#include <SDk/Engine.hpp>

#include <Maths/Algorithms.hpp>

#include <SDK/Systems/PhysicSystem.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>

#define DEBUG_NO_FIXED_UPDATE 1

namespace Pe
{
	bool PhysicSystem::Init()
	{
		if (PhysicSystemInfos::broadPhases.size() != 0)
			mBroadPhaseIndex = 0;

		if (PhysicSystemInfos::narrowPhases.size() != 0)
			mNarrowPhaseIndex = 0;

		return true;
	}
	void PhysicSystem::UnInit()
	{
		for (auto it = PhysicSystemInfos::broadPhases.begin(); it != PhysicSystemInfos::broadPhases.end(); ++it)
			delete *it;

		PhysicSystemInfos::broadPhases.clear();


		for (auto it = PhysicSystemInfos::narrowPhases.begin(); it != PhysicSystemInfos::narrowPhases.end(); ++it)
			delete *it;

		PhysicSystemInfos::narrowPhases.clear();

		mAABBs.clear();
		mBodies.clear();
	}

	void PhysicSystem::StartNewComponents() noexcept
	{
		for (auto it = mToStartAABBs.begin(); it != mToStartAABBs.end(); ++it)
		{
			(*it)->Start();
			mAABBs.push_back(*it);
		}

		mToStartAABBs.clear();

		for (auto it = mToStartBodies.begin(); it != mToStartBodies.end(); ++it)
		{
			(*it)->Start();
			mBodies.push_back(*it);
		}

		mToStartBodies.clear();
	}

	void PhysicSystem::Update(float _frameTime)
	{
		StartNewComponents();


		// Update AABBs.
		for (auto it = mAABBs.begin(); it != mAABBs.end(); ++it)
			(*it)->Update(_frameTime);

		// Update bodies.
		for (auto it = mBodies.begin(); it != mBodies.end(); ++it)
			(*it)->Update(_frameTime);


		DrawDebug();

	// No frametime for draw debug.
	#if SAT_DEUBG || GJK_DEBUG || DEBUG_NO_FIXED_UPDATE
		FixedUpdate(_frameTime);
		return;
	#endif

		mCurrTime += _frameTime;

		if (mCurrTime < PhysicSystemInfos::fixedTime)
			return;

		int step = static_cast<int>(mCurrTime / PhysicSystemInfos::fixedTime);

		// mCurrTime Modulo fixedTime.
		mCurrTime = Algo::FMod(mCurrTime, PhysicSystemInfos::fixedTime);

		FixedUpdate(PhysicSystemInfos::fixedTime * step);
	}
	void PhysicSystem::FixedUpdate(float _fixedTime)
	{
		DebugInfos debugInfos;

		sChrono.Start();

		// FixedUpdate AABB.
		for (auto it = mAABBs.begin(); it != mAABBs.end(); ++it)
			(*it)->FixedUpdate(0.0f);

		debugInfos.AABBUpdateTime = sChrono.Stop() * 1000.0f;

		// Execute BroadPhase
		if (mBroadPhaseIndex >= 0)
		{
			mBroadPhasePairs.clear();
			mCollisions.clear();

			sChrono.Start();

			PhysicSystemInfos::broadPhases[mBroadPhaseIndex]->Execute(mBodies, mBroadPhasePairs);

			debugInfos.broadPhaseTime = sChrono.Stop() * 1000.0f;
			debugInfos.broadPhasePairNum = mBroadPhasePairs.size();

			if (mBroadPhasePairs.size() <= 0)
			{
				debugInfos.narrowPhaseTime = debugInfos.collisionResponseTime = 0.0f;
				debugInfos.narrowPhasePairNum = 0;
			}
			else if (mNarrowPhaseIndex >= 0)
			{
				// Execute NarrowPhase
				sChrono.Start();

				PhysicSystemInfos::narrowPhases[mNarrowPhaseIndex]->Execute(mBroadPhasePairs, mCollisions);

				debugInfos.narrowPhaseTime = sChrono.Stop() * 1000.0f;
				debugInfos.narrowPhasePairNum = mCollisions.size();


				// Execute Collision Responses.
				sChrono.Start();

				UpdateCollisionResponses();

				debugInfos.collisionResponseTime = sChrono.Stop() * 1000.0f;
			}
		}

		// FixedUpdate bodies.
		sChrono.Start();

		for (auto it = mBodies.begin(); it != mBodies.end(); ++it)
			(*it)->FixedUpdate(_fixedTime);

		debugInfos.bodyUpdateTime = sChrono.Stop() * 1000.0f;
		UpdateDebugText(debugInfos);
	}

	void PhysicSystem::UpdateCollisionResponses()
	{
		for (unsigned int i = 0; i < mCollisions.size(); ++i)
		{
			CollisionInfos& infos = mCollisions[i];
			CollisionInfos reversedInfos = infos.GetReversed();

			if (infos.first->IsStatic())
				ComputeWallCollisionResponses(reversedInfos);		// Wall response.
			else if (infos.second->IsStatic())
				ComputeWallCollisionResponses(infos);				// Wall response.
			else
				ComputeCollisionResponses(infos);					// Body response.

			// Trigger body collisions.
			infos.first->OnCollision(infos);
			infos.second->OnCollision(reversedInfos);
		}
	}

	void PhysicSystem::ComputeWallCollisionResponses(const CollisionInfos& _infos)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_infos.first);

		if (fBody->isKinematic || !fBody->useCollisionResponse)
			return;

		ApplyWallPositionCorrection(_infos);
		
		for (auto it = _infos.collisionPoints.begin(); it != _infos.collisionPoints.end(); ++it)
		{
			float impulse = ApplyWallImpulse(_infos, *it);

			if (impulse != 0.0f)
				ApplyWallFriction(_infos, *it, impulse);
		}
	}
	void PhysicSystem::ApplyWallPositionCorrection(const CollisionInfos& _infos)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_infos.first);

		Vec2 normal;
		float correction = 0.0f;

;		for (auto it = _infos.collisionPoints.begin(); it != _infos.collisionPoints.end(); ++it)
		{
			correction += it->penetration;
			normal += it->normal;
		}

		correction *= fBody->mass / _infos.collisionPoints.size();
		normal /= static_cast<float>(_infos.collisionPoints.size());

		fBody->gObj->tr.pos += normal * (1.0f / fBody->mass) * correction;
	}
	float PhysicSystem::ApplyWallImpulse(const BodyPair& _pair, const CollisionPointInfos& _infos)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_pair.first);
		StaticBody* const sBody = static_cast<StaticBody*>(_pair.second);

		// Delta rotations.
		Vec2 fDeltaRot = _infos.point - fBody->gObj->tr.pos;

		// Compute velocities
		Vec2 fVel = fBody->linearVelocity + fDeltaRot.GetNormal() * fBody->angularVelocity;
		

		// Velocity relative.
		float vRel = fVel.Dot(_infos.normal);

		// Body velocyties don't face each other.
		if (vRel > 0.0f)
			return 0.0f;


		// Inverse mass.
		float fInvMass = 1.0f / fBody->mass;

		// Average bounciness.
		float avBounce = (fBody->bounciness + sBody->bounciness) / 2.0f;


		// Compute momentums.
		float fMomentum = Vec2::Cross(fDeltaRot, _infos.normal) / fBody->GetInertiaTensor();

		// Compute weight rotation
		float fWeightRot = (fDeltaRot.GetNormal() * fMomentum).Dot(_infos.normal);


		// Compute impulse.
		float impulse = -(avBounce + 1.0f) * vRel / (fInvMass + fWeightRot);


		// Velocity change.
		fBody->linearVelocity += _infos.normal * impulse * fInvMass;
		fBody->angularVelocity += fMomentum * impulse;

		return impulse;
	}
	void PhysicSystem::ApplyWallFriction(const BodyPair& _pair, const CollisionPointInfos& _infos, float _collisionImpulse)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_pair.first);
		StaticBody* const sBody = static_cast<StaticBody*>(_pair.second);

		float fInvMass = 1.0f / fBody->mass;

		// Average static frictioc.
		float avSFriction = (fBody->staticFriction + sBody->staticFriction) / 2.0f;

		// Velocity relative.
		Vec2 vRel = fBody->linearVelocity;

		// Tangent and tangent velocity relative.
		Vec2 tan = vRel - _infos.normal * vRel.Dot(_infos.normal);

		// Bad tangent.
		if (tan.GetSqrNorm() == 0.0f)
			return;

		tan.Normalize();
		float vTan = vRel.Dot(tan);

		// Compute impulse.
		float frictionImpulse = -vTan / fInvMass;

		// clamp to collision impulse max.
		frictionImpulse = Algo::Clamp(frictionImpulse, -Algo::Abs(_collisionImpulse) * avSFriction, Algo::Abs(_collisionImpulse) * avSFriction);

		// Velocity change.
		fBody->linearVelocity += tan * frictionImpulse * fInvMass;
	}

	void PhysicSystem::ComputeCollisionResponses(const CollisionInfos& _infos)
	{
		ApplyPositionCorrection(_infos);

		for (auto it = _infos.collisionPoints.begin(); it != _infos.collisionPoints.end(); ++it)
		{
			float impulse = ApplyImpulse(_infos, *it);

			if (impulse != 0.0f)
				ApplyFriction(_infos, *it, impulse);
		}
	}
	void PhysicSystem::ApplyPositionCorrection(const CollisionInfos& _infos)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_infos.first);
		DynamicBody* const sBody = static_cast<DynamicBody*>(_infos.second);

		float fInvMass = 1.0f / fBody->mass;
		float sInvMass = 1.0f / sBody->mass;
		static constexpr float damping = 0.5f;

		float correction = 0.0f;
		Vec2 normal;

		for (auto it = _infos.collisionPoints.begin(); it != _infos.collisionPoints.end(); ++it)
		{
			correction += it->penetration;
			normal += it->normal;
		}

		correction = (correction * damping) / (fInvMass + sInvMass) / _infos.collisionPoints.size();
		normal /= static_cast<float>(_infos.collisionPoints.size());

		if (!fBody->isKinematic && fBody->useCollisionResponse)
			fBody->gObj->tr.pos += normal * fInvMass * correction;
		if (!sBody->isKinematic && sBody->useCollisionResponse)
			sBody->gObj->tr.pos -= normal * sInvMass * correction;
	}
	float PhysicSystem::ApplyImpulse(const BodyPair& _pair, const CollisionPointInfos& _infos)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_pair.first);
		DynamicBody* const sBody = static_cast<DynamicBody*>(_pair.second);

		// Delta rotations.
		Vec2 fDeltaRot = _infos.point - fBody->gObj->tr.pos;
		Vec2 sDeltaRot = _infos.point - sBody->gObj->tr.pos;


		// Compute velocities
		Vec2 fVel = fBody->linearVelocity + fDeltaRot.GetNormal() * fBody->angularVelocity;
		Vec2 sVel = sBody->linearVelocity + sDeltaRot.GetNormal() * sBody->angularVelocity;


		// Velocity relative.
		float vRel = (fVel - sVel).Dot(_infos.normal);

		// Body velocyties don't face each other.
		if (vRel > 0.0f)
			return 0.0f;


		// Inverse mass.
		float fInvMass = 1.0f / fBody->mass;
		float sInvMass = 1.0f / sBody->mass;


		// Average bounciness.
		float avBounce = (fBody->bounciness + sBody->bounciness) / 2.0f;


		// Compute momentums.
		float fMomentum = Vec2::Cross(fDeltaRot, _infos.normal) / fBody->GetInertiaTensor();
		float sMomentum = Vec2::Cross(sDeltaRot, _infos.normal) / sBody->GetInertiaTensor();


		// Compute weight rotation
		float fWeightRot = (fDeltaRot.GetNormal() * fMomentum).Dot(_infos.normal);
		float sWeightRot = (sDeltaRot.GetNormal() * sMomentum).Dot(_infos.normal);


		// Compute impulse.
		float impulse = -(avBounce + 1.0f) * vRel / (fInvMass + sInvMass + fWeightRot + sWeightRot);


		// Velocity change.
		if (!fBody->isKinematic && fBody->useCollisionResponse)
		{
			fBody->linearVelocity += _infos.normal * impulse * fInvMass;
			fBody->angularVelocity += fMomentum * impulse;
		}
		if (!sBody->isKinematic && sBody->useCollisionResponse)
		{
			sBody->linearVelocity -= _infos.normal * impulse * sInvMass;
			sBody->angularVelocity -= sMomentum * impulse;
		}

		return impulse;
	}
	void PhysicSystem::ApplyFriction(const BodyPair& _pair, const CollisionPointInfos& _infos, float _collisionImpulse)
	{
		DynamicBody* const fBody = static_cast<DynamicBody*>(_pair.first);
		DynamicBody* const sBody = static_cast<DynamicBody*>(_pair.second);

		float fInvMass = 1.0f / fBody->mass;
		float sInvMass = 1.0f / sBody->mass;

		// Average static frictioc.
		float avSFriction = (fBody->staticFriction + sBody->staticFriction) / 2.0f;

		// Velocity relative.
		Vec2 vRel = (fBody->linearVelocity - sBody->linearVelocity);

		// Tangent and tangent velocity relative.
		Vec2 tan = vRel - _infos.normal * vRel.Dot(_infos.normal);

		// Bad tangent.
		if (tan.GetSqrNorm() == 0.0f)
			return;

		tan.Normalize();
		float vTan = vRel.Dot(tan);

		// Compute impulse.
		float frictionImpulse = -vTan / (fInvMass + sInvMass);

		// clamp to collision impulse max.
		frictionImpulse = Algo::Clamp(frictionImpulse, -Algo::Abs(_collisionImpulse) * avSFriction, Algo::Abs(_collisionImpulse) * avSFriction);

		// Velocity change.
		if (!fBody->isKinematic && fBody->useCollisionResponse)
			fBody->linearVelocity += tan * frictionImpulse * fInvMass;
		if (!sBody->isKinematic && sBody->useCollisionResponse)
			sBody->linearVelocity -= tan * frictionImpulse * sInvMass;
	}

	void PhysicSystem::SwitchKey(Key _key)
	{
		if (_key == Key::K_F6)
		{
			LOG("PhysicSystem::SwitchKey(_key): Switch BroadPhase", LogLevel::Normal);

			if (PhysicSystemInfos::broadPhases.size() <= 1)
				return;

			if (mBroadPhaseIndex < 0)
			{
				mBroadPhaseIndex = 0;
				return;
			}

			PhysicSystemInfos::broadPhases[mBroadPhaseIndex]->Reset();
			mBroadPhaseIndex = ++mBroadPhaseIndex % PhysicSystemInfos::broadPhases.size();
		}
		else if (_key == Key::K_F7)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle BroadPhase debug: " + std::to_string(drawBroadPhaseDebug), LogLevel::Normal);

			drawBroadPhaseDebug = !drawBroadPhaseDebug;
		}
		else if (_key == Key::K_F8)
		{
			LOG("PhysicSystem::SwitchKey(_key): Switch NarrowPhase", LogLevel::Normal);

			if (PhysicSystemInfos::narrowPhases.size() <= 1)
				return;

			if (mNarrowPhaseIndex < 0)
			{
				mNarrowPhaseIndex = 0;
				return;
			}

			PhysicSystemInfos::narrowPhases[mNarrowPhaseIndex]->Reset();
			mNarrowPhaseIndex = ++mNarrowPhaseIndex % PhysicSystemInfos::narrowPhases.size();
		}
		else if (_key == Key::K_F9)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle NarrowPhase debug: " + std::to_string(drawNarrowPhaseDebug), LogLevel::Normal);

			drawNarrowPhaseDebug = !drawNarrowPhaseDebug;
		}
		else if (_key == Key::K_UP)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle Gravity up", LogLevel::Normal);

			PhysicSystemInfos::gravityInfos.force = Vec2(0.0f, 9.81f);
		}
		else if (_key == Key::K_DOWN)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle Gravity down", LogLevel::Normal);

			PhysicSystemInfos::gravityInfos.force = Vec2(0.0f, -9.81f);
		}
		else if (_key == Key::K_LEFT)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle Gravity left", LogLevel::Normal);

			PhysicSystemInfos::gravityInfos.force = Vec2(-9.81f, 0.0f);
		}
		else if (_key == Key::K_RIGHT)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle Gravity right", LogLevel::Normal);

			PhysicSystemInfos::gravityInfos.force = Vec2(9.81f, 0.0f);
		}
		else if (_key == Key::K_G)
		{
			LOG("PhysicSystem::SwitchKey(_key): Toogle Gravity", LogLevel::Normal);

			if(PhysicSystemInfos::gravityInfos.force.GetSqrNorm() != 0.0f)
				PhysicSystemInfos::gravityInfos.force = Vec2(0.0f, 0.0f);
			else
				PhysicSystemInfos::gravityInfos.force = Vec2(0.0f, -9.81f);
		}
	}

	void PhysicSystem::Reset()
	{
		for (auto it = mAABBs.begin(); it != mAABBs.end(); ++it)
			(*it)->End();

		for (auto it = mBodies.begin(); it != mBodies.end(); ++it)
			(*it)->End();

		mBodies.clear();
		mAABBs.clear();

		mToStartBodies.clear();
		mToStartAABBs.clear();

		if(mBroadPhaseIndex >= 0)
			PhysicSystemInfos::broadPhases[mBroadPhaseIndex]->Reset();
		
		if (mNarrowPhaseIndex >= 0)
			PhysicSystemInfos::narrowPhases[mNarrowPhaseIndex]->Reset();
	}

	void PhysicSystem::Register(BodyBase* _body) noexcept
	{
		mToStartBodies.push_back(_body);
	}
	void PhysicSystem::Register(AABBComponent* _aabb) noexcept
	{
		mToStartAABBs.push_back(_aabb);
	}

	void PhysicSystem::DrawDebug()
	{
		if (Debug::sDrawDebugFlags == DrawDebugState::None)
			return;

		Debug::DrawText(mDebugText);

		if (Debug::sDrawDebugFlags >= DrawDebugState::RecapLandmarksAABB)
		{
			for (auto it = mAABBs.begin(); it != mAABBs.end(); ++it)
				(*it)->DrawDebug();
		}

		if (drawBroadPhaseDebug && mBroadPhaseIndex >= 0)
			PhysicSystemInfos::broadPhases[mBroadPhaseIndex]->DrawDebug();

		if (drawNarrowPhaseDebug && mNarrowPhaseIndex >= 0)
		{
			PhysicSystemInfos::narrowPhases[mNarrowPhaseIndex]->DrawDebug();

			for (auto it = mCollisions.begin(); it != mCollisions.end(); ++it)
				it->DrawDebug();
		}
	}
	void PhysicSystem::UpdateDebugText(const DebugInfos& _infos)
	{
		mDebugText = "PhysicSystem: " + std::to_string(_infos.AABBUpdateTime + _infos.broadPhaseTime + _infos.narrowPhaseTime + _infos.bodyUpdateTime) +
			" ms\n        F6: Switch BroadPhase        F7: Toogle BroadPhase Debug " + std::to_string(drawBroadPhaseDebug) +
			"\n        F8: Switch NarrowPhase        F9: Toogle NarrowPhase Debug " + std::to_string(drawNarrowPhaseDebug) + "\n        " + std::to_string(mBodies.size()) +
			" bodies\n        AABB: " + std::to_string(_infos.AABBUpdateTime) + "ms";

		if (mBroadPhaseIndex >= 0)
		{
			mDebugText += "\n        BroadPhase: " + std::to_string(_infos.broadPhaseTime) + "ms    Pairs: " + std::to_string(_infos.broadPhasePairNum) + "        " + PhysicSystemInfos::broadPhases[mBroadPhaseIndex]->GetDebugName();

			if (mNarrowPhaseIndex >= 0)
			{
				mDebugText += "\n        NarrowPhase: " + std::to_string(_infos.narrowPhaseTime) + "ms    Pairs: " + std::to_string(_infos.narrowPhasePairNum) + "        " + PhysicSystemInfos::narrowPhases[mNarrowPhaseIndex]->GetDebugName();

				mDebugText += "\n        CollisionResponse: " + std::to_string(_infos.collisionResponseTime) + "ms";
			}
		}

		mDebugText += "\n        Body: " + std::to_string(_infos.bodyUpdateTime) + "ms";
	}
}
#include <Core/Debug.hpp>

#include <Maths/Algorithms.hpp>

#include <SDK/Physics/CollisionInfos.hpp>

#include <SDK/Systems/Infos/PhysicSystemInfos.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>

namespace Pe
{
	float DynamicBody::GetInertiaTensor() const
	{
		return mass * mShapeInertia;
	}
	float DynamicBody::GetInverseInertiaTensor() const
	{
		return 1.0f / GetInertiaTensor();
	}

	void DynamicBody::Start() noexcept
	{
		mShapeInertia = aabb->GetShape()->ComputeShapeIntertia();
	}

	void DynamicBody::FixedUpdate(float _fixedTime) noexcept
	{
		if (isKinematic)
			return;

		ComputeLinearForces(_fixedTime);
		ComputeAngularForces(_fixedTime);
	}

	Vec2 DynamicBody::ComputeLinearForce(const ForceInfos& fInfos, float _fixedTime)
	{
		/** Compute lineaar acceleration. */

		switch (fInfos.forceMode)
		{
		case ForceMode::Force:
			return (fInfos.force / mass) * _fixedTime;
		case ForceMode::Impulse:
			return fInfos.force / mass;
		case ForceMode::Acceleration:
			return fInfos.force * _fixedTime;
		case ForceMode::Velocity:
			return fInfos.force;
		default:
			LOG("DynamicBody::ComputeLinearForce(fInfos): ForceMode not supported yet!", LogLevel::Error);
			return Vec2(0.0f, 0.0f);
		}
	}
	float DynamicBody::ComputeAngularForce(const ForceInfos& fInfos, float _fixedTime)
	{
		/** Compute torque. */
	
		float torque = Vec2::Cross(fInfos.localPoint, fInfos.force);

		switch (fInfos.forceMode)
		{
		case ForceMode::Force:
			return torque / GetInertiaTensor() * _fixedTime;
		case ForceMode::Impulse:
			return torque / GetInertiaTensor();
		case ForceMode::Acceleration:
			return torque * _fixedTime;
		case ForceMode::Velocity:
			return torque;
		default:
			LOG("DynamicBody::ComputeAngularForce(fInfos): ForceMode not supported yet!", LogLevel::Error);
			return 0.0f;
		}
	}

	void DynamicBody::ComputeLinearForces(float _fixedTime)
	{
		// Add Gravity
		if (useGravity)
			linearVelocity += ComputeLinearForce(PhysicSystemInfos::gravityInfos, _fixedTime);

		for (auto it = mLinearForces.begin(); it != mLinearForces.end(); ++it)
		{
			// Add force to current velocity.
			linearVelocity += ComputeLinearForce(*it, _fixedTime);
		}

		// Clear applied forces.
		mLinearForces.clear();

		// Apply body constraints.
		ApplyLinearConstraints();

		// Apply drag force.
		linearVelocity *= 1 - _fixedTime * linearDrag;

		// Apply velocity to body.
		gObj->tr.pos += linearVelocity * _fixedTime;
	}
	void DynamicBody::ComputeAngularForces(float _fixedTime)
	{
		// Compute sum of each Force.
		for (auto it = mAngularForces.begin(); it != mAngularForces.end(); ++it)
		{
			// Add force to current velocity.
			angularVelocity += ComputeAngularForce(*it, _fixedTime);
		}

		// Clear applied forces.
		mAngularForces.clear();

		// Apply drag force.
		angularVelocity *= 1 - _fixedTime * angularDrag;

		// Apply velocity to body.
		gObj->tr.rot.Rotate(Algo::RadToDeg * angularVelocity * _fixedTime);
	}

	void DynamicBody::ApplyLinearConstraints()
	{
		if (linearConstraints & (unsigned int)ForceConstraints::FreezeX)
			linearVelocity.x = 0.0f;

		if (linearConstraints & (unsigned int)ForceConstraints::FreezeY)
			linearVelocity.y = 0.0f;
	}

	void DynamicBody::AddForce(const ForceParams& _fParams) noexcept
	{
		if (isKinematic)
			return;

		ForceInfos forceInfos
		{
			_fParams.shouldNormalize ? _fParams.force.GetNormalized() : _fParams.force,
			_fParams.forceMode
		};

		switch (_fParams.motionMode)
		{
		case MotionMode::Linear:
			mLinearForces.push_back(forceInfos);
			break;
		case MotionMode::Angular:
			mAngularForces.push_back(forceInfos);
			break;
		default:
			LOG("DynamicBody::AddForce(_params): MotionMode not supported yet!", LogLevel::Error);
			break;
		}
	}

	bool DynamicBody::IsStatic() const
	{
		return false;
	}
	void DynamicBody::OnCollision(const CollisionInfos& _infos) noexcept
	{
	}
}
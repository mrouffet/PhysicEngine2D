#pragma once

#ifndef PE_PHYSIC_SYSTEM_GUARD
#define PE_PHYSIC_SYSTEM_GUARD

#include <vector>

#include <SDK/Systems/SystemBase.hpp>
#include <SDK/Systems/Infos/PhysicSystemInfos.hpp>

#include <SDK/Scene/Components/Physics/BodyBase.hpp>
#include <SDK/Scene/Components/Physics/AABBComponent.hpp>

namespace Pe
{
	class PhysicSystem : public SystemBase
	{
		struct DebugInfos
		{
			float AABBUpdateTime = 0.0f;

			float broadPhaseTime = 0.0f;
			unsigned int broadPhasePairNum = 0;

			float narrowPhaseTime = 0.0f;
			unsigned int narrowPhasePairNum = 0;

			float collisionResponseTime = 0.0f;

			float bodyUpdateTime = 0.0f;
		};

		std::string mDebugText;

		int mBroadPhaseIndex = -1;
		int mNarrowPhaseIndex = -1;

		float mCurrTime = 0.0f;

		std::vector<BodyBase*> mToStartBodies;
		std::vector<AABBComponent*> mToStartAABBs;

		std::vector<BodyBase*> mBodies;
		std::vector<AABBComponent*> mAABBs;

		std::vector<BodyPair> mBroadPhasePairs;
		std::vector<CollisionInfos> mCollisions;

		void FixedUpdate(float _fixedTime);

		void StartNewComponents() noexcept;

		void UpdateCollisionResponses();

		void ComputeWallCollisionResponses(const CollisionInfos& _infos);
		void ApplyWallPositionCorrection(const CollisionInfos& _infos);
		float ApplyWallImpulse(const BodyPair& _pair, const CollisionPointInfos& _infos);
		void ApplyWallFriction(const BodyPair& _pair, const CollisionPointInfos& _infos, float _collisionImpulse);

		void ComputeCollisionResponses(const CollisionInfos& _infos);
		void ApplyPositionCorrection(const CollisionInfos& _infos);
		float ApplyImpulse(const BodyPair& _pair, const CollisionPointInfos& _infos);
		void ApplyFriction(const BodyPair& _pair, const CollisionPointInfos& _infos, float _collisionImpulse);

		void DrawDebug();
		void UpdateDebugText(const DebugInfos& _infos);

	public:
		// Debug
		bool drawBroadPhaseDebug = false;
		bool drawNarrowPhaseDebug = false;

		bool Init() override final;
		void UnInit() override final;

		void Update(float _frameTime) override final;

		void SwitchKey(Key _key) override final;

		void Reset() override final;

		void Register(BodyBase* _body) noexcept;
		void Register(AABBComponent* _aabb) noexcept;
	};
}

#endif // GUARD
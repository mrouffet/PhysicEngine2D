#pragma once

#ifndef PE_COLLISION_INFOS_GUARD
#define PE_COLLISION_INFOS_GUARD

#include <vector>

#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	struct CollisionPointInfos
	{
		Vec2 normal;
		Vec2 point;
		float penetration = 0.0f;

		CollisionPointInfos() = default;
		CollisionPointInfos(const Vec2& _normal, const Vec2& _point, float _penetration = 0.0f) noexcept;

		void DrawDebug() const;
	};

	struct CollisionInfos : public BodyPair
	{
		std::vector<CollisionPointInfos> collisionPoints;

		CollisionInfos(BodyBase* _first, BodyBase* _second) noexcept;
		CollisionInfos(const BodyPair& _pair) noexcept;

		CollisionInfos& Reversed() noexcept;
		CollisionInfos GetReversed() const noexcept;

		void DrawDebug() const;
	};
}

#endif // GUARD
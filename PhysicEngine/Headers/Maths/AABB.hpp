#pragma once

#ifndef PE_AABB_GUARD
#define PE_AABB_GUARD

#include <Maths/Vec2.hpp>

namespace Pe
{
	class AABB
	{
	public:
		Vec2 min;
		Vec2 max;

		AABB() = default;
		AABB(const AABB& _first, const AABB& _second);

		bool IsCollidingX(const AABB& _other) const;
		bool IsCollidingY(const AABB& _other) const;
		bool IsColliding(const AABB& _other) const;

		float ComputeWidth() const;
		float ComputeHeight() const;

		Vec2 ComputeCenter() const;

		float ComputeArea() const;
	};
}

#endif // GUARD
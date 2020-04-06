#include <Maths/Algorithms.hpp>

#include <Maths/AABB.hpp>

namespace Pe
{
	AABB::AABB(const AABB& _first, const AABB& _second)
	{
		min.x = Algo::Min(_first.min.x, _second.min.x);
		min.y = Algo::Min(_first.min.y, _second.min.y);

		max.x = Algo::Max(_first.max.x, _second.max.x);
		max.y = Algo::Max(_first.max.y, _second.max.y);
	}

	bool AABB::IsCollidingX(const AABB& _other) const
	{
		// Check out of X bound.
		return !(min.x > _other.max.x || max.x < _other.min.x);
	}
	bool AABB::IsCollidingY(const AABB& _other) const
	{
		// Check out of Y bound.
		return !(min.y > _other.max.y || max.y < _other.min.y);
	}
	bool AABB::IsColliding(const AABB& _other) const
	{
		return IsCollidingX(_other) && IsCollidingY(_other);
	}

	float AABB::ComputeWidth() const
	{
		return max.x - min.x;
	}
	float AABB::ComputeHeight() const
	{
		return max.y - min.y;
	}

	Vec2 AABB::ComputeCenter() const
	{
		return min + (max - min) / 2.0f;
	}

	float AABB::ComputeArea() const
	{
		return ComputeWidth() * ComputeHeight();
	}
}
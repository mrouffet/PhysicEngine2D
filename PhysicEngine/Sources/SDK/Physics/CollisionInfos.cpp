#include <SDK/Engine.hpp>

#include <SDK/Physics/CollisionInfos.hpp>

namespace Pe
{
	// CollisionPointInfos
	CollisionPointInfos::CollisionPointInfos(const Vec2& _normal, const Vec2& _point, float _penetration) noexcept :
		normal{ _normal },
		point{ _point },
		penetration{ _penetration }
	{
	}

	void CollisionPointInfos::DrawDebug() const
	{
		// Draw point + penetration.
		Debug::DrawLine(
			point,
			point + normal * -penetration,
			Color{ 0.75f, 0.0f, 0.75f }
		);

		// Draw point location.
		Debug::DrawLine(
			Vec2(),
			point,
			Color{ 0.0f, 0.65f, 0.45f }
		);

		// Draw point text at location.
		Debug::DrawText("CollisionPoint", point - Vec2(2.0f, 0.0f) + normal, Vec2(0.9f, 0.9f), Color{1.0f, 0.5f, 0.5f});
	}


	// CollisionInfos
	CollisionInfos::CollisionInfos(BodyBase* _first, BodyBase* _second) noexcept : BodyPair(_first, _second)
	{
	}
	CollisionInfos::CollisionInfos(const BodyPair& _pair) noexcept : BodyPair(_pair)
	{
	}

	CollisionInfos& CollisionInfos::Reversed() noexcept
	{
		BodyBase* temp = first;
		first = second;
		second = temp;

		for (auto it = collisionPoints.begin(); it != collisionPoints.end(); ++it)
			it->normal = -it->normal;

		return *this;
	}
	CollisionInfos CollisionInfos::GetReversed() const noexcept
	{
		CollisionInfos result(*this);
		result.Reversed();

		return result;
	}

	void CollisionInfos::DrawDebug() const
	{
		for (auto it = collisionPoints.begin(); it != collisionPoints.end(); ++it)
			it->DrawDebug();
	}
}
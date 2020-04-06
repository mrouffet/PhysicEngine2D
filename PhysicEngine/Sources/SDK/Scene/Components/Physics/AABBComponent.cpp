#include <Maths/Algorithms.hpp>

#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/Physics/AABBComponent.hpp>

namespace Pe
{
	ShapeComponent* AABBComponent::GetShape() const noexcept
	{
		return mShape;
	}

	void AABBComponent::Start() noexcept
	{
		mShape = gObj->GetComponent<ShapeComponent>();

		ASSERT(mShape, "AABBComponent::Start(): ShapeComponent nullptr!");
	}

	void AABBComponent::FixedUpdate(float _fixedTime) noexcept
	{
		min = Vec2(FLT_MAX, FLT_MAX);
		max = Vec2(-FLT_MAX, -FLT_MAX);

		const std::vector<Vec2>& points = mShape->GetPoints();

		for(auto it = points.begin(); it != points.end(); ++it)
		{
			const Vec2& point = *it;

			min.x = Algo::Min(point.x, min.x);
			min.y = Algo::Min(point.y, min.y);

			max.x = Algo::Max(point.x, max.x);
			max.y = Algo::Max(point.y, max.y);
		}
	}

	void AABBComponent::Register() noexcept
	{
		Engine::GetPhysicSystem().Register(this);
	}

	void AABBComponent::DrawDebug() noexcept
	{
		Debug::DrawRectangle(*this, Color{0.0f, 0.75f, 0.0f});
	}
}
#include <utility>

#include <Maths/Algorithms.hpp>

#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/ShapeComponent.hpp>

namespace Pe
{
	std::shared_ptr<ShapeHandle> ShapeHandle::Create(const Shape* _shape)
	{
		return std::make_shared<ShapeHandle>(ShapeHandle{ _shape });
	}


	ShapeComponent::ShapeComponent(GameObj* _obj, const Shape* _shape) noexcept :
		Component(_obj),
		mHandle(ShapeHandle::Create(_shape))
	{
		mWorldPoints.resize(mHandle->shape->pointNum);
	}
	ShapeComponent::ShapeComponent(GameObj* _obj, std::shared_ptr<ShapeHandle> _shapeHandle) noexcept :
		Component(_obj),
		mHandle(_shapeHandle)
	{
		mWorldPoints.resize(mHandle->shape->pointNum);
	}

	std::shared_ptr<ShapeHandle> ShapeComponent::GetHandle() const
	{
		return mHandle;
	}
	const std::vector<Vec2>& ShapeComponent::GetPoints() const noexcept
	{
		return mWorldPoints;
	}

	bool ShapeComponent::IsPointInside(Vec2 _point) const noexcept
	{
		float maxDist = -FLT_MAX;

		const unsigned int pointNum = mHandle->shape->pointNum;

		for (unsigned int i = 0; i < pointNum; ++i)
		{
			float pointDist = (_point - mWorldPoints[i]).Dot(mWorldPoints[i] - mWorldPoints[(i + 1) % pointNum]);

			maxDist = Algo::Max(maxDist, pointDist);
		}

		return maxDist <= 0.0f;
	}

	float ShapeComponent::ComputeShapeIntertia() const
	{
		return mHandle->shape->ComputeShapeIntertia();
	}

	Vec2 ShapeComponent::ComputeCentroid() const
	{
		return gObj->tr.rot * mHandle->shape->ComputeCentroid() + gObj->tr.pos;
	}

	void ShapeComponent::Update(float _frameTime) noexcept
	{
		Component::Update(_frameTime);

		// Update world positions.

		for (unsigned int i = 0; i < mHandle->shape->pointNum; ++i)
			mWorldPoints[i] = gObj->tr.rot * mHandle->shape->GetPoint(i) + gObj->tr.pos;
	}
}
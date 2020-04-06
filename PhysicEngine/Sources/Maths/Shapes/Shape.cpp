#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	Shape::Shape(unsigned int _pointNum, const Vec2* _points) :
		pointNum{ _pointNum },
		mPoints{ _points }
	{
	}

	Shape::Shape(Shape&& _other) noexcept :
		pointNum{_other.pointNum },
		mPoints{ _other.mPoints }
	{
		_other.mPoints = nullptr;
	}
	Shape::Shape(const Shape& _other) noexcept : pointNum{ _other.pointNum }
	{
		Vec2* points = new Vec2[pointNum];

		for (unsigned int i = 0; i < pointNum; ++i)
			points[i] = _other.mPoints[i];

		mPoints = points;
	}

	Shape::~Shape()
	{
		delete[] mPoints;
	}

	const Vec2& Shape::GetPoint(unsigned int _index) const noexcept
	{
		return mPoints[_index];
	}

	float Shape::ComputeShapeIntertia() const noexcept
	{
		return 1.0f;
	}

	Vec2 Shape::ComputeCentroid() const noexcept
	{
		return Vec2();
	}
}
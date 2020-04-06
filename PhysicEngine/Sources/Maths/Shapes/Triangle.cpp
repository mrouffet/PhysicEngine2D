#include <Maths/Shapes/Triangle.hpp>

namespace Pe
{
	Triangle::Triangle(float _base, float _height) :
		Shape(
			3,
			new Vec2[3]{
				{ -_base * 0.5f, -_height * 0.5f },
				{ _base * 0.5f, -_height * 0.5f },
				{ 0.0f, _height * 0.5f }
			}
		),
		base{ _base },
		height{ _height }
	{
	}

	bool Triangle::IsPointIn(const Vec2* const _triangle, const Vec2& _point)
	{
		float d1 = Vec2::Sign(_point, _triangle[0], _triangle[1]);
		float d2 = Vec2::Sign(_point, _triangle[1], _triangle[2]);
		float d3 = Vec2::Sign(_point, _triangle[2], _triangle[0]);

		if (d1 < 0.0f)
			return d2 < 0.0f && d3 < 0.0f;

		return d2 > 0.0f && d3 > 0.0f;
	}

	float Triangle::ComputeShapeIntertia() const noexcept
	{
		// ToDo: Implement.
		return 1.0f;
	}

	Vec2 Triangle::ComputeCentroid() const noexcept
	{
		return (mPoints[0] + mPoints[1] + mPoints[2]) / 3.0f;
	}
}
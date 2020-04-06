#include <Maths/Shapes/Circle.hpp>

#include <Maths/Algorithms.hpp>

namespace Pe
{
	Circle::Circle(float _radius) :
		Shape(sCirclePointNum, Init(_radius)),
		radius{ _radius }
	{
	}

	Vec2* Circle::Init(float _radius)
	{
		Vec2* points = new Vec2[sCirclePointNum];

		constexpr float dRadAngle = 360.0f / sCirclePointNum * Algo::DegToRad;

		for (unsigned int i = 0u; i < sCirclePointNum; ++i)
		{
			float angle = i * dRadAngle;

			points[i] = Vec2(Algo::Cos(angle), Algo::Sin(angle)) * _radius;
		}

		return points;
	}

	float Circle::ComputeShapeIntertia() const noexcept
	{
		// 1/2 * radius2
		return 0.5f * radius * radius;
	}
}
#include <Core/Random.hpp>

#include <Maths/Algorithms.hpp>
#include <Maths/Shapes/RandomShape.hpp>

namespace Pe
{
	RandomShape::RandomShape(const InitParams& _params) : Shape(_params.pointNum, _params.points)
	{
	}
	RandomShape::RandomShape(const RandomShapeParams& _params) : RandomShape(Init(_params))
	{
	}

	RandomShape::InitParams RandomShape::Init(const RandomShapeParams& _params)
	{
		InitParams initParams;

		initParams.pointNum = Random::Value(_params.minPoints, _params.maxPoints + 1);

		initParams.points = new Vec2[initParams.pointNum];
		float dAngle = 360.0f / (float)initParams.pointNum;
		float radius = Random::Value(_params.minRadius, _params.maxRadius);

		for (size_t i = 0; i < initParams.pointNum; ++i)
		{
			float angle = i * dAngle + Random::Value(-dAngle / 3.0f, dAngle / 3.0f);
			float dist = radius;

			Vec2 point = Vec2(cosf(angle * Algo::DegToRad), sinf(angle * Algo::DegToRad)) * dist;
			initParams.points[i] = point;
		}

		return initParams;
	}

	float RandomShape::ComputeShapeIntertia() const noexcept
	{
		//TODO: Implement
		return 1.0f;
	}
}
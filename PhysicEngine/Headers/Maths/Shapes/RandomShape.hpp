#pragma once

#ifndef PE_RANDOM_SHAPE_GUARD
#define PE_RANDOM_SHAPE_GUARD

#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	struct RandomShapeParams
	{
		unsigned int minPoints = 0u;
		unsigned int maxPoints = 2u;

		float minRadius = 0.0f;
		float maxRadius = 1.0f;
	};

	class RandomShape : public Shape
	{
		struct InitParams
		{
			unsigned int pointNum;
			Vec2* points;
		};

		InitParams Init(const RandomShapeParams& _params);

		RandomShape(const InitParams& _params);

	public:
		RandomShape(const RandomShapeParams& _params);

		float ComputeShapeIntertia() const noexcept override final;
	};
}

#endif // GUARD
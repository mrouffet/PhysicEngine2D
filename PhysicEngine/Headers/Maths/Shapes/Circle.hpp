#pragma once

#ifndef PE_SPHERE_GUARD
#define PE_SPHERE_GUARD

#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	class Circle : public Shape
	{
		static constexpr unsigned int sCirclePointNum = 20u;

		static Vec2* Init(float _radius);

	public:
		const float radius = 1.0f;

		Circle(float _radius);

		float ComputeShapeIntertia() const noexcept override final;
	};
}

#endif // GUARD
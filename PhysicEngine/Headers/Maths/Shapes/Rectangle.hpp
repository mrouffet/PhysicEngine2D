#pragma once

#ifndef PE_RECTANGLE_GUARD
#define PE_RECTANGLE_GUARD

#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	class Rectangle : public Shape
	{
	public:
		const float width = 1.0f;
		const float height = 1.0f;

		Rectangle(float _width, float _height);

		float ComputeShapeIntertia() const noexcept override final;

		Vec2 ComputeCentroid() const noexcept override final;
	};
}

#endif // GUARD
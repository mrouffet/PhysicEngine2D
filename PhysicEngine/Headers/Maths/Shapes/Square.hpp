#pragma once

#ifndef PE_SQUARE_GUARD
#define PE_SQUARE_GUARD

#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	class Square : public Shape
	{
	public:
		const float edge = 1.0f;

		Square(float _edge);

		float ComputeShapeIntertia() const noexcept override final;

		Vec2 ComputeCentroid() const noexcept override final;
	};
}

#endif // GUARD
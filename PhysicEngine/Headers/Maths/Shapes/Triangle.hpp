#pragma once

#ifndef PE_TRIANGLE_GUARD
#define PE_TRIANGLE_GUARD

#include <Maths/Shapes/Shape.hpp>

namespace Pe
{
	class Triangle : public Shape
	{
	public:
		const float base = 1.0f;
		const float height = 1.0f;

		Triangle(float _base, float _height);

		static bool IsPointIn(const Vec2* const _triangle, const Vec2& _point);

		float ComputeShapeIntertia() const noexcept override final;

		Vec2 ComputeCentroid() const noexcept override final;
	};
}

#endif // GUARD
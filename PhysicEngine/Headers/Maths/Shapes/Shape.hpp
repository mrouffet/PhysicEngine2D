#pragma once

#ifndef PE_SHAPE_GUARD
#define PE_SHAPE_GUARD

#include <Maths/Vec2.hpp>

namespace Pe
{
	class Shape
	{
	protected:
		const Vec2* mPoints = nullptr;

	public:
		const unsigned int pointNum;

		Shape(unsigned int _pointNum, const Vec2* _points);
		Shape(Shape&& _other) noexcept;
		Shape(const Shape& _other) noexcept;
		~Shape();

		const Vec2& GetPoint(unsigned int _index) const noexcept;

		// Inertia tensor without mass.
		virtual float ComputeShapeIntertia() const noexcept;

		virtual Vec2 ComputeCentroid() const noexcept;
	};
}

#endif // GUARD
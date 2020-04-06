#include <Maths/Shapes/Square.hpp>

namespace Pe
{
	Square::Square(float _edge) :
		Shape(
			4,
			new Vec2[4]{
				{ -_edge * 0.5f, -_edge * 0.5f },
				{ _edge * 0.5f, -_edge * 0.5f },
				{ _edge * 0.5f, _edge * 0.5f },
				{ -_edge * 0.5f, _edge * 0.5f }
			}
		),
		edge{_edge}
	{
	}

	float Square::ComputeShapeIntertia() const noexcept
	{
		// 1/12 * (w2 + h2)
		return 1.0f / 6.0f * edge * edge;
	}

	Vec2 Square::ComputeCentroid() const noexcept
	{
		return mPoints[0] + (mPoints[2] - mPoints[0]) * 0.5f;
	}
}
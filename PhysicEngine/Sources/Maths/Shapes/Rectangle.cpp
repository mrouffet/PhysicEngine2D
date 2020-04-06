#include <Maths/Shapes/Rectangle.hpp>

namespace Pe
{
	Rectangle::Rectangle(float _width, float _height) :
		Shape(
			4,
			new Vec2[4]{
				{ -_width * 0.5f, -_height * 0.5f },
				{ _width * 0.5f, -_height * 0.5f },
				{ _width * 0.5f, _height * 0.5f },
				{ -_width * 0.5f, _height * 0.5f }
			}
		),
		width{ _width },
		height{ _height }
	{
	}

	float Rectangle::ComputeShapeIntertia() const noexcept
	{
		// 1/12 * (w2 + h2)

		return 1.0f / 12.0f * (width * width + height * height);
	}

	Vec2 Rectangle::ComputeCentroid() const noexcept
	{
		return mPoints[0] + (mPoints[2] - mPoints[0]) * 0.5f;
	}
}
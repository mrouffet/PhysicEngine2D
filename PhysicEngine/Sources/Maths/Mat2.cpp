#include <Maths/Algorithms.hpp>
#include <Maths/Mat2.hpp>

namespace Pe
{
	Mat2::Mat2(float _a, float _b, float _c, float _d) noexcept :
		x(_a, _c),
		y(_b, _d)
	{
	}

	Mat2 Mat2::GetInverse() const noexcept
	{
		return Mat2(x.x, x.y, y.x, y.y);
	}

	float Mat2::GetAngle() const noexcept
	{
		return Vec2(1.0f, 0.0f).GetAngle(x);
	}
	void Mat2::SetAngle(float _deg) noexcept
	{
		float c = Algo::Cos(_deg * Algo::DegToRad);
		float s = Algo::Sin(_deg * Algo::DegToRad);

		x.x = c;
		x.y = s;

		y.x = -s;
		y.y = c;
	}

	void Mat2::Rotate(float _deg) noexcept
	{
		Mat2 matRot;
		matRot.SetAngle(_deg);
		*this = *this * matRot;
	}

	Mat2 Mat2::operator*(const Mat2& _rhs) const noexcept
	{
		return Mat2(
			x.x*_rhs.x.x + y.x*_rhs.x.y,
			x.x*_rhs.y.x + y.x*_rhs.y.y,
			x.y*_rhs.x.x + y.y*_rhs.x.y,
			x.y*_rhs.y.x + y.y*_rhs.y.y
		);
	}
	Vec2 Mat2::operator*(const Vec2& _rhs) const noexcept
	{
		return Vec2(
			x.x*_rhs.x + y.x*_rhs.y,
			x.y*_rhs.x + y.y*_rhs.y
		);
	}
}
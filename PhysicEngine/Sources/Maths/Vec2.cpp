#include <Maths/Algorithms.hpp>
#include <Maths/Vec2.hpp>

namespace Pe
{
	Vec2::Vec2(float _x, float _y) noexcept :
		x{ _x },
		y{ _y }
	{
	}

	float Vec2::GetNorm() const noexcept
	{
		return Algo::Sqrt(GetSqrNorm());
	}
	float Vec2::GetSqrNorm() const noexcept
	{
		return x * x + y * y;
	}

	void Vec2::Normalize() noexcept
	{
		float norm = GetNorm();

		x /= norm;
		y /= norm;
	}
	Vec2 Vec2::GetNormalized() const noexcept
	{
		float norm = GetNorm();

		return Vec2(x / norm, y / norm);
	}

	float Vec2::GetAngle(const Vec2& _to) noexcept
	{
		float cosAngle = Algo::Clamp(GetNormalized() | _to.GetNormalized(), -1.0f, 1.0f);
		float angle = Algo::ACos(cosAngle) * Algo::RadToDeg * Algo::Sign(*this ^ _to);
		
		return angle;
	}
	Vec2 Vec2::GetNormal() const noexcept
	{
		return Vec2(-y, x);
	}

	float Vec2::GetSlope() const noexcept
	{
		if (x == 0.0f)
			return 0.0f;

		return y / x;
	}

	void Vec2::Reflect(Vec2 normal, float elasticity) noexcept
	{
		*this = *this - normal * (1.0f + elasticity) * (*this | normal);
	}

	float Vec2::Dot(const Vec2& _other) const noexcept
	{
		return x * _other.x + y * _other.y;
	}
	float Vec2::Cross(const Vec2& _other) const noexcept
	{
		return x * _other.y - y * _other.x;
	}

	float Vec2::Dot(const Vec2& _v1, const Vec2& _v2) noexcept
	{
		return _v1.Dot(_v2);
	}
	float Vec2::Cross(const Vec2& _v1, const Vec2& _v2) noexcept
	{
		return _v1.Cross(_v2);
	}

	float Vec2::Sign(const Vec2& _v1, const Vec2& _v2, const Vec2& _v3)
	{
		return (_v1.x - _v3.x) * (_v2.y - _v3.y) - (_v2.x - _v3.x) * (_v1.y - _v3.y);
	}

	Vec2 Vec2::operator-() const noexcept
	{
		return Vec2(-x, -y);
	}

	Vec2 Vec2::operator+(const Vec2& _rhs) const noexcept
	{
		return Vec2(x + _rhs.x, y + _rhs.y);
	}
	Vec2 Vec2::operator-(const Vec2& _rhs) const noexcept
	{
		return Vec2(x - _rhs.x, y - _rhs.y);
	}

	Vec2 Vec2::operator*(float _factor) const noexcept
	{
		return Vec2(x * _factor, y * _factor);
	}
	Vec2 Vec2::operator/(float _factor) const noexcept
	{
		return Vec2(x / _factor, y / _factor);
	}

	float Vec2::operator|(const Vec2& _rhs) const noexcept
	{
		return Dot(_rhs);
	}
	float Vec2::operator^(const Vec2& _rhs) const noexcept
	{
		return Cross(_rhs);
	}

	Vec2& Vec2::operator+=(const Vec2& _rhs) noexcept
	{
		x += _rhs.x;
		y += _rhs.y;

		return *this;
	}
	Vec2& Vec2::operator-=(const Vec2& _rhs) noexcept
	{
		x -= _rhs.x;
		y -= _rhs.y;

		return *this;
	}

	Vec2& Vec2::operator*=(float _factor) noexcept
	{
		x *= _factor;
		y *= _factor;

		return *this;
	}
	Vec2& Vec2::operator/=(float _factor) noexcept
	{
		x /= _factor;
		y /= _factor;

		return *this;
	}

	bool Vec2::operator==(const Vec2& _rhs) const noexcept
	{
		return Algo::NearlyEqual(x, _rhs.x) && Algo::NearlyEqual(x, _rhs.x);
	}
	bool Vec2::operator!=(const Vec2& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}
}
#pragma once

#ifndef PE_VEC2_GUARD
#define PE_VEC2_GUARD

namespace Pe
{
	class Vec2
	{
	public:
		float x = 0.0f;
		float y = 0.0f;

		Vec2() = default;
		Vec2(float _x, float _y) noexcept;
		float GetNorm() const noexcept;
		float GetSqrNorm() const noexcept;

		void Normalize() noexcept;
		Vec2 GetNormalized() const noexcept;

		float GetAngle(const Vec2& _to) noexcept;
		Vec2 GetNormal() const noexcept;

		float GetSlope() const noexcept;

		void Reflect(Vec2 normal, float elasticity = 1.0f) noexcept;

		float Dot(const Vec2& _other) const noexcept;
		float Cross(const Vec2& _other) const noexcept;

		static float Dot(const Vec2& _v1, const Vec2& _v2) noexcept;
		static float Cross(const Vec2& _v1, const Vec2& _v2) noexcept;

		static float Sign(const Vec2& _v1, const Vec2& _v2, const Vec2& _v3);

		Vec2 operator-() const noexcept;

		Vec2 operator+(const Vec2& _rhs) const noexcept;
		Vec2 operator-(const Vec2& _rhs) const noexcept;

		Vec2 operator*(float _factor) const noexcept;
		Vec2 operator/(float _factor) const noexcept;

		float operator|(const Vec2& _rhs) const noexcept;
		float operator^(const Vec2& _rhs) const noexcept;

		Vec2& operator+=(const Vec2& _rhs) noexcept;
		Vec2& operator-=(const Vec2& _rhs) noexcept;

		Vec2& operator*=(float _factor) noexcept;
		Vec2& operator/=(float _factor) noexcept;

		bool operator==(const Vec2& _rhs) const noexcept;
		bool operator!=(const Vec2& _rhs) const noexcept;
	};
}

#endif // GUARD
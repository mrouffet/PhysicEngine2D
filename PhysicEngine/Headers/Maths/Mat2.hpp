#pragma once

#ifndef PE_MAT2_GUARD
#define PE_MAT2_GUARD

#include <Maths/Vec2.hpp>

namespace Pe
{
	class Mat2
	{
	public:
		Vec2 x = Vec2(1.0f, 0.0f);
		Vec2 y = Vec2(0.0f, 1.0f);

		Mat2() = default;
		Mat2(float _a, float _b, float _c, float _d) noexcept;

		Mat2 GetInverse() const noexcept;
		
		float GetAngle() const noexcept;
		void SetAngle(float _deg) noexcept;

		void Rotate(float _deg) noexcept;

		Mat2 operator*(const Mat2& _rhs) const noexcept;
		Vec2 operator*(const Vec2& _rhs) const noexcept;
	};
}

#endif // GUARD
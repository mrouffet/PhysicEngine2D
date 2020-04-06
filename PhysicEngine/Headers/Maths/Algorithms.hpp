#pragma once

#ifndef PE_ALGORITHMS_GUARD
#define PE_ALGORITHMS_GUARD

namespace Pe
{
	namespace Algo
	{
		constexpr double PI = 3.14159265358979323846;
		constexpr float RadToDeg = static_cast<float>(180.0f / PI);
		constexpr float DegToRad = static_cast<float>(PI / 180.0f);
		constexpr float Epsilon = 0.000001f;

		template <typename T>
		T Min(T _a, T _b) noexcept;
		template <typename T>
		T Max(T _a, T _b) noexcept;

		template<typename T>
		T Clamp(T _val, T _min, T _max) noexcept;

		float Cos(float _rad) noexcept;
		float ACos(float _cos) noexcept;
		float Sin(float _rad) noexcept;
		float ASin(float _sin) noexcept;

		float Sqrt(float _in) noexcept;

		float Sign(float _a) noexcept;
		float Abs(float _a) noexcept;
		float FMod(float _lhs, float _rhs) noexcept;

		bool NearlyEqual(float _lhs, float _rhs, float epsilon = Epsilon);
	}
}

#include <Maths/Algorithms.inl>

#endif // GUARD
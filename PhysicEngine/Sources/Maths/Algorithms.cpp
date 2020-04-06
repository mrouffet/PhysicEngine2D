#include <Maths/Algorithms.hpp>

#include <cmath>

namespace Pe
{
	namespace Algo
	{
		float Cos(float _rad) noexcept
		{
			return cosf(_rad);
		}
		float ACos(float _cos) noexcept
		{
			return acosf(_cos);
		}
		float Sin(float _rad) noexcept
		{
			return sinf(_rad);
		}
		float ASin(float _sin) noexcept
		{
			return asinf(_sin);
		}

		float Sqrt(float _in) noexcept
		{
			return sqrtf(_in);
		}

		float Sign(float _a) noexcept
		{
			return _a > 0.0f ? 1.0f : -1.0f;
		}
		float Abs(float _a) noexcept
		{
			return _a * Sign(_a);
		}
		float FMod(float _lhs, float _rhs) noexcept
		{
			return fmod(_lhs, _rhs);
		}

		bool NearlyEqual(float _lhs, float _rhs, float epsilon)
		{
			return Abs(_lhs - _rhs) < epsilon;
		}
	}
}
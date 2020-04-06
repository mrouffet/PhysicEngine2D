#pragma once

#ifndef PE_RANDOM_GUARD
#define PE_RANDOM_GUARD

#include <cstdlib>

namespace Pe
{
	class Random
	{
		static Random RandomInitRAII;

		Random() noexcept;

	public:
		template <typename T>
		static T Value(T _min, T _max) noexcept;
	};
}

#include <Core/Random.inl>

#endif // GUARD
#pragma once

#ifndef PE_PAIR_GUARD
#define PE_PAIR_GUARD

namespace Pe
{
	template <typename T1, typename T2>
	struct Pair
	{
		T1 first;
		T2 second;

		Pair(T1 _first, T2 _second) noexcept;

		Pair GetReversed() const noexcept;

		static Pair Reverse(const Pair& _pair) noexcept;
	};
}

#include <Core/Pair.inl>

#endif // GUARD
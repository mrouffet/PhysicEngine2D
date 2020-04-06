#pragma once

#ifndef PE_HULL_GUARD
#define PE_HULL_GUARD

#include <vector>

#include <Maths/Vec2.hpp>

namespace Pe
{
	class Hull
	{
		template <typename T>
		static void Graham(std::vector<T>& _cloudPoint) noexcept;

	public:
		template <typename T>
		static void Create(std::vector<T>& _cloudPoint) noexcept;
	};
}

#include <Maths/Hull.inl>

#endif // GUARD
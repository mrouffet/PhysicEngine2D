#pragma once

#ifndef PE_TRANSFORM_GUARD
#define PE_TRANSFORM_GUARD

#include <array>

#include <Maths/Vec2.hpp>
#include <Maths/Mat2.hpp>

namespace Pe
{
	struct Transform
	{
		Vec2 pos;
		Mat2 rot;
		Vec2 scale = Vec2(1.0f, 1.0f);

		std::array<float, 16> GetMatrix() const noexcept;
	};
}

#endif // GUARD
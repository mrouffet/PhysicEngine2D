#include <Maths/Transform.hpp>

namespace Pe
{
	std::array<float, 16> Transform::GetMatrix() const noexcept
	{
		return std::array<float, 16> {
			rot.x.x * scale.x, rot.x.y, 0.0f, 0.0f,
			rot.y.x, rot.y.y * scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			pos.x, pos.y, -1.0f, 1.0f
		};
	}
}
#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/Render/Ortho/RenderOrtho.hpp>

namespace Pe
{
	void RenderOrtho::Register() noexcept
	{
		Engine::GetRenderSystem().Register(this);
	}
}
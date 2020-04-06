#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderPersp.hpp>

namespace Pe
{
	void RenderPersp::Register() noexcept
	{
		Engine::GetRenderSystem().Register(this);
	}
}
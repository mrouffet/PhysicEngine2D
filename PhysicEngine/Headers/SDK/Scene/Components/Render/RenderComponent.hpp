#pragma once

#ifndef PE_RENDER_COMPONENT_GUARD
#define PE_RENDER_COMPONENT_GUARD

#include <Core/Color.hpp>

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	class RenderComponent : public Component
	{
	public:
		using Component::Component;

		Color color = Color{ 1.0f, 1.0f, 1.0f };

		virtual void Draw() noexcept = 0;
	};
}

#endif // GUARD
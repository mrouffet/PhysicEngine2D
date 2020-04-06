#pragma once

#ifndef PE_RENDER_ORTHOGRAPHIC_GUARD
#define PE_RENDER_ORTHOGRAPHIC_GUARD

#include <SDK/Scene/Components/Render/RenderComponent.hpp>

namespace Pe
{
	class RenderOrtho : public RenderComponent
	{
	public:
		using RenderComponent::RenderComponent;

		void Register() noexcept override;
	};
}

#endif // GUARD
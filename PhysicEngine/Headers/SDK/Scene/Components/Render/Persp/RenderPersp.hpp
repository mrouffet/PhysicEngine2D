#pragma once

#ifndef PE_RENDER_PERSPECTIVE_GUARD
#define PE_RENDER_PERSPECTIVE_GUARD

#include <SDK/Scene/Components/Render/RenderComponent.hpp>

namespace Pe
{
	class RenderPersp : public RenderComponent
	{
	public:
		using RenderComponent::RenderComponent;

		void Register() noexcept override final;
	};
}

#endif // GUARD
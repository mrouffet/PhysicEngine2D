#pragma once

#ifndef PE_RENDER_TEXT_GUARD
#define PE_RENDER_TEXT_GUARD

#include <string>

#include <SDK/Scene/Components/Render/Ortho/RenderOrtho.hpp>

namespace Pe
{
	class RenderText : public RenderOrtho
	{
	public:
		using RenderOrtho::RenderOrtho;

		std::string text;

		void Draw() noexcept override;
	};
}

#endif // GUARD
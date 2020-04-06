#pragma once

#ifndef PE_DEBUG_TEXT_GUARD
#define PE_DEBUG_TEXT_GUARD

#include <SDK/Scene/Components/Render/Ortho/RenderText.hpp>

namespace Pe
{
	namespace Debug
	{
		void DrawText(const std::string& _str);
		void DrawText(const std::string& _str, const Vec2& _pos, const Vec2& _scale = Vec2(1.0f, 1.0f), const Color& _color = Color{1.0f, 1.0f, 1.0f});
	}

	class DebugText : public RenderText
	{
		float mLowFrameTime = FLT_MAX;
		float mHighFrameTime = -FLT_MAX;
		float mCountFrameTime = 0.0f;
		float mCurrFPSTime = 0.0f;

		std::string mFPSText;

	public:
		using RenderText::RenderText;

		void Update(float _frameTime) noexcept override final;

		void Draw() noexcept override final;

		void Register() noexcept override final;
	};
}

#endif // GUARD
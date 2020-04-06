#pragma once

#ifndef PE_RENDER_SYSTEM_GUARD
#define PE_RENDER_SYSTEM_GUARD

#include <vector>

#include <Renderer/Window.hpp>

#include <SDK/Systems/SystemBase.hpp>
#include <SDK/Systems/Infos/RenderSystemInfos.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderPersp.hpp>
#include <SDK/Scene/Components/Render/Ortho/RenderOrtho.hpp>

namespace Pe
{
	class RenderSystem : public SystemBase
	{
		Window mWin;
		struct dtx_font* mFont = nullptr;

		std::vector<RenderPersp*> mToStartPerspRenders;
		std::vector<RenderOrtho*> mToStartOrthoRenders;

		std::vector<RenderPersp*> mPerspRenders;
		std::vector<RenderOrtho*> mOrthoRenders;

		void SetRenderColor(const Color& _color);

		void PreRenderFrame();

		void SetPerpectiveProjectionMatrix();
		void RenderPerspectives();

		void SetOrthographicProjectionMatrix();
		void RenderOrthographics();

		void StartNewComponents();

	public:
		float worldScale = 1.0f;

		const Window& GetWindow() const noexcept;

		const std::vector<RenderPersp*>& GetPerspRenders() const noexcept;

		Vec2 GetMousePosition() const noexcept;
		Vec2 GetWorldMousePosition() const noexcept;

		bool Init() override final;
		void UnInit() override final;

		void Resize(int _windowWidth, int _windowHeight);

		void Update(float _frameTime) override final;

		void SwitchKey(Key _key) override final;

		void Reset() override final;

		void Register(RenderPersp* _render) noexcept;
		void Register(RenderOrtho* _render) noexcept;
	};
}

#endif // GUARD
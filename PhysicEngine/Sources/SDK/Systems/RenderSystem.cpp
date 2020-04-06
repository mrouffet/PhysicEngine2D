#include <drawtext.h>

#include <SDk/Engine.hpp>

#include <SDK/Systems/RenderSystem.hpp>

#include <SDK/Systems/Infos/PhysicSystemInfos.hpp>

namespace Pe
{
	const Window& RenderSystem::GetWindow() const noexcept
	{
		return mWin;
	}

	const std::vector<RenderPersp*>& RenderSystem::GetPerspRenders() const noexcept
	{
		return mPerspRenders;
	}

	Vec2 RenderSystem::GetMousePosition() const noexcept
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		y = mWin.GetHeight() - y;

		return Vec2((float)x, (float)y);
	}
	Vec2 RenderSystem::GetWorldMousePosition() const noexcept
	{
		Vec2 mousePos = GetMousePosition();
		float height = (float)mWin.GetHeight();

		return (mousePos - Vec2((float)mWin.GetWidth(), (float)height) * 0.5f) * (worldScale / height);
	}

	bool RenderSystem::Init()
	{
		// Init Window
		ASSERT(
			mWin.Create(
				RenderSystemInfos::appName,
				static_cast<int>(RenderSystemInfos::windowDimention.x),
				static_cast<int>(RenderSystemInfos::windowDimention.y)
			),
			"RenderEngine::Init(): Create window", true
		);

		// Init Font
		mFont = dtx_open_font("font.ttf", 16);
		ASSERT(mFont, "RenderEngine::Init(): Create font", true);
		dtx_use_font(mFont, 16);

		return true;
	}
	void RenderSystem::UnInit()
	{
		Reset();

		dtx_close_font(mFont);
		mFont = nullptr;

		mWin.Destroy();
	}

	void RenderSystem::SetRenderColor(const Color& _color)
	{
		glColor3f(_color.r, _color.g, _color.b);
	}

	void RenderSystem::PreRenderFrame()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderSystem::SetPerpectiveProjectionMatrix()
	{
		float ratio = static_cast<float>(mWin.GetWidth()) / static_cast<float>(mWin.GetHeight());

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-worldScale * 0.5f * ratio, worldScale * 0.5f * ratio, -worldScale * 0.5f, worldScale * 0.5f, 0.1f, 10.0f);

		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.0f, 0.0f, 0.0f); // move camera here
	}
	void RenderSystem::RenderPerspectives()
	{
		SetPerpectiveProjectionMatrix();

		for (unsigned int i = 0; i < mPerspRenders.size(); ++i)
		{
			if (mPerspRenders[i]->isEnable)
			{
				SetRenderColor(mPerspRenders[i]->color);
				mPerspRenders[i]->Draw();
			}
		}
	}

	void RenderSystem::SetOrthographicProjectionMatrix()
	{
		// Set proj matrix to screen space
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, mWin.GetWidth(), 0, mWin.GetHeight(), -1, 1);

		// Reset model matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	void RenderSystem::RenderOrthographics()
	{
		SetOrthographicProjectionMatrix();

		glPushMatrix();

		for (unsigned int i = 0; i < mOrthoRenders.size(); ++i)
		{
			if (mOrthoRenders[i]->isEnable)
			{
				SetRenderColor(mOrthoRenders[i]->color);
				mOrthoRenders[i]->Draw();
			}
		}

		glPopMatrix();
	}

	void RenderSystem::Resize(int _windowWidth, int _windowHeight)
	{
		mWin.Resize(_windowWidth, _windowHeight);
	}

	void RenderSystem::StartNewComponents()
	{
		for (auto it = mToStartPerspRenders.begin(); it != mToStartPerspRenders.end(); ++it)
		{
			(*it)->Start();
			mPerspRenders.push_back(*it);
		}

		mToStartPerspRenders.clear();

		for (auto it = mToStartOrthoRenders.begin(); it != mToStartOrthoRenders.end(); ++it)
		{
			(*it)->Start();
			mOrthoRenders.push_back(*it);
		}

		mToStartOrthoRenders.clear();
	}

	void RenderSystem::Update(float _frameTime)
	{
		sChrono.Start();

		StartNewComponents();

		PreRenderFrame();

		RenderPerspectives();
		RenderOrthographics();

		mWin.Update();

		Debug::DrawText("RenderSystem: " + std::to_string(sChrono.Stop() * 1000.0f) + "ms");

		if (Debug::sDrawDebugFlags >= DrawDebugState::Landmarks)
		{
			// Landmarks
			Debug::DrawLine(Vec2(-1000.0f, 0.0f), Vec2(1000.0f, 0.0f), Color{ 0.35f, 0.35f, 0.35f });
			Debug::DrawLine(Vec2(0.0f, -1000.0f), Vec2(0.0f, 1000.0f), Color{ 0.35f, 0.35f, 0.35f });

			// Gravity debug.
			Debug::DrawLine(Vec2(0.0f, 0.0f), PhysicSystemInfos::gravityInfos.force, Color{ 1.0f, 0.35f, 0.5f });
		}
	}

	void RenderSystem::SwitchKey(Key _key)
	{
	}

	void RenderSystem::Reset()
	{
		for (auto it = mPerspRenders.begin(); it != mPerspRenders.end(); ++it)
			(*it)->End();

		for (auto it = mOrthoRenders.begin(); it != mOrthoRenders.end(); ++it)
			(*it)->End();

		mPerspRenders.clear();
		mOrthoRenders.clear();

		mToStartPerspRenders.clear();
		mToStartOrthoRenders.clear();
	}

	void RenderSystem::Register(RenderPersp* _render) noexcept
	{
		mToStartPerspRenders.push_back(_render);
	}
	void RenderSystem::Register(RenderOrtho* _render) noexcept
	{
		mToStartOrthoRenders.push_back(_render);
	}
}
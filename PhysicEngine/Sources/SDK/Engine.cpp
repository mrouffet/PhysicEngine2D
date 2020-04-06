#include <SDK/Engine.hpp>

namespace Pe
{
	Engine* Engine::sInstance = nullptr;

#if GJK_DEBUG
	unsigned int Engine::GJK_INDEX = 0;
#endif

	bool Engine::Init()
	{
		ASSERT(!sInstance, "Engine::Init(_infos):: Engine instance init", true);

		sInstance = this;

		// Init Physics System.
		ASSERT(mPhysicSystem.Init(), "Engine::Init(): PhysicSystem init", true);

		// Init Renderer System.
		ASSERT(mRenderSystem.Init(), "Engine::Init(): RenderSystem init", true);

		// Init Scene System.
		mSceneSystem.onSetWorldScale = &Engine::WorldScaleEvent;
		ASSERT(mSceneSystem.Init(), "Engine::Init(): mSceneMgr init", true);

		// Init Input System.
		mInputSystem.onResizeEvent = &Engine::ResizeEvent;
		mInputSystem.onKeyPressed = &Engine::InputEvent;
		ASSERT(mInputSystem.Init(), "Engine::Init(): InputSystem init", true);

		return true;
	}
	void Engine::UnInit()
	{
		sInstance = nullptr;

		mInputSystem.UnInit();
		mRenderSystem.UnInit();
		mPhysicSystem.UnInit();
		mSceneSystem.UnInit();
	}

	void Engine::Launch()
	{
		ASSERT(Init(), "Engine::Start(): Engine initialization");

		Update();

		UnInit();
	}

	void Engine::Update()
	{
		LOG("Engine::Update()", LogLevel::Info);

		Chrono frameChrono;
		float frameTime = 0.0f;
		
		frameChrono.Start();

		while (mInputSystem.ProcessEvents())
		{
			frameTime = frameChrono.Restart();

			mPhysicSystem.Update(frameTime);
			mRenderSystem.Update(frameTime);
			mSceneSystem.Update(frameTime);
			mInputSystem.Update(frameTime);

			UpdateLockFPS(frameChrono);
		}
	}

	void Engine::UpdateLockFPS(Chrono& _frameChrono)
	{
		if (mFPS == FPS::Unlocked)
			return;
		
		float currTime = 0.0f;
		float frameTimeLimit = (mFPS == FPS::Locked30) ? 1.0f / 30.0f : 1.0f / 60.0f;

		do
		{
			currTime = _frameChrono.Stop();
		}
		while (currTime < frameTimeLimit);
	}

	void Engine::Reset()
	{
		mPhysicSystem.Reset();
		mRenderSystem.Reset();
		mSceneSystem.Reset();
		mInputSystem.Reset();
	}

	FPS Engine::GetFPS() const
	{
		return mFPS;
	}

	Engine& Engine::GetInstance()
	{
#if PE_ENGINE_SAFE
		ASSERT(sInstance, "Engine::GetInstance(): Instance nullptr!");
#endif

		return *sInstance;
	}

	PhysicSystem& Engine::GetPhysicSystem()
	{
		return GetInstance().mPhysicSystem;
	}
	RenderSystem& Engine::GetRenderSystem()
	{
		return GetInstance().mRenderSystem;
	}
	SceneSystem& Engine::GetSceneSystem()
	{
		return GetInstance().mSceneSystem;
	}
	InputSystem& Engine::GetInputSystem()
	{
		return GetInstance().mInputSystem;
	}

	void Engine::InputEvent(Key _key)
	{
		Engine& en = GetInstance();

		en.mPhysicSystem.SwitchKey(_key);
		en.mRenderSystem.SwitchKey(_key);
		en.mSceneSystem.SwitchKey(_key);
		en.mInputSystem.SwitchKey(_key);

		if (_key == Key::K_F1)
		{
			Debug::sDrawDebugFlags = static_cast<DrawDebugState>((static_cast<unsigned int>(Debug::sDrawDebugFlags) + 1) % static_cast<unsigned int>(DrawDebugState::Count));
			LOG("Engine::InputEvent(_key): Toogle Draw Debug: " + std::to_string(static_cast<unsigned int>(Debug::sDrawDebugFlags)), LogLevel::Normal);
		}
		else if (_key == Key::K_F2)
		{
			sInstance->mFPS = static_cast<FPS>((static_cast<int>(sInstance->mFPS) + 1) % static_cast<int>(FPS::Count));

			std::string enumLog = sInstance->mFPS == FPS::Unlocked ? "Unlocked" : sInstance->mFPS == FPS::Locked30 ? "30" : "60";
			LOG("Engine::InputEvent(_key): Toogle FPS: " + enumLog, LogLevel::Normal);
		}
#if GJK_DEBUG
		else if (_key == Key::K_C)
			++GJK_INDEX;
#endif
	}

	void Engine::ResizeEvent(int _width, int _height)
	{
		GetRenderSystem().Resize(static_cast<int>(_width), static_cast<int>(_height));
	}
	void Engine::WorldScaleEvent(float _worldScale)
	{
		GetRenderSystem().worldScale = _worldScale;
	}
}
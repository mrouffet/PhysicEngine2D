#pragma once

#ifndef PE_ENGINE_GUARD_GUARD
#define PE_ENGINE_GUARD_GUARD

#include <array>

#include <Core/Debug.hpp>
#include <Core/FPS.hpp>
#include <Core/Chrono.hpp>

#include <SDK/Miscs/Config.hpp>

#include <SDK/Systems/InputSystem.hpp>
#include <SDK/Systems/RenderSystem.hpp>
#include <SDK/Systems/PhysicSystem.hpp>
#include <SDK/Systems/SceneSystem.hpp>

#include <SDK/Scene/Components/Render/Ortho/DebugText.hpp>
#include <SDK/Scene/Components/Render/Persp/DebugPersp.hpp>

namespace Pe
{
	class Engine
	{
		static Engine* sInstance;

		FPS mFPS = FPS::Unlocked;

		PhysicSystem mPhysicSystem;
		RenderSystem mRenderSystem;
		SceneSystem mSceneSystem;
		InputSystem mInputSystem;

		bool Init();
		void UnInit();

		void Update();

		void UpdateLockFPS(Chrono& _frameChrono);

		// Events bind to std::function.
		static void InputEvent(Key _key);
		static void ResizeEvent(int _width, int _height);
		static void WorldScaleEvent(float _worldScale);

	public:
#if GJK_DEBUG
		static unsigned int GJK_INDEX;
#endif

		void Launch();

		void Reset();

		FPS GetFPS() const;

		// Engine Getters.
		static Engine& GetInstance();

		static PhysicSystem& GetPhysicSystem();
		static RenderSystem& GetRenderSystem();
		static SceneSystem& GetSceneSystem();
		static InputSystem& GetInputSystem();
	};
}

#endif // GUARD
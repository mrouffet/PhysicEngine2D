#pragma once

#ifndef PE_INPUT_SYSTEM_GUARD
#define PE_INPUT_SYSTEM_GUARD

#include <functional>
#include <unordered_map>

#include <Core/Key.hpp>

#include <SDK/Systems/SystemBase.hpp>

namespace Pe
{
	class InputSystem : public SystemBase
	{
		std::unordered_map<Key, bool> mPressedKeyMap;

	public:
		std::function<void(Key)> onKeyPressed;
		std::function<void(Key)> onKeyReleased;
		std::function<void(int, int)> onResizeEvent;
		std::function<void(int)> onMouseWheel;

		bool Init() override final;
		void UnInit() override final;

		bool ProcessEvents();

		bool IsKeyDown(Key _key) const;
		bool IsKeyUp(Key _key) const;

		bool GetMouseButton(int _button) const;

		void Update(float _frameTime) override final;

		void SwitchKey(Key _key) override final;

		void Reset() override final;
	};
}

#endif // GUARD
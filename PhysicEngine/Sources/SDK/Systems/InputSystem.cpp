#include <SDL.h>

#include <SDK/Systems/InputSystem.hpp>

namespace Pe
{
	bool InputSystem::Init()
	{
		mPressedKeyMap.reserve((unsigned int)Key::Count);

		return true;
	}
	void InputSystem::UnInit()
	{
		onKeyPressed = nullptr;
		onKeyReleased = nullptr;
		onResizeEvent = nullptr;
		onMouseWheel = nullptr;

		mPressedKeyMap.clear();
	}

	void InputSystem::Update(float _frameTime)
	{
	}

	void InputSystem::SwitchKey(Key _key)
	{
	}

	void InputSystem::Reset()
	{
		mPressedKeyMap.clear();
	}

	bool InputSystem::ProcessEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return false;

			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					if (onResizeEvent != nullptr)
						onResizeEvent(event.window.data1, event.window.data2);
				break;
				}
			break;

			case SDL_KEYDOWN:
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return false;

				Key key = static_cast<Key>(event.key.keysym.scancode);

				if (onKeyPressed != nullptr)
					onKeyPressed(key);

				mPressedKeyMap[key] = true;
				break;
			}
			case SDL_KEYUP:
			{
				Key key = static_cast<Key>(event.key.keysym.scancode);

				if (onKeyReleased != nullptr)
					onKeyReleased(key);

				mPressedKeyMap[key] = false;
				break;
			}
			case SDL_MOUSEWHEEL:
				if (onMouseWheel != nullptr)
					onMouseWheel(event.wheel.y);
				break;
			}
		}

		return true;
	}

	bool InputSystem::IsKeyDown(Key _key) const
	{
		auto it = mPressedKeyMap.find(_key);

		if (it == mPressedKeyMap.end())
			return false;

		return it->second;
	}
	bool InputSystem::IsKeyUp(Key _key) const
	{
		auto it = mPressedKeyMap.find(_key);

		if (it == mPressedKeyMap.end())
			return true;

		return it->second;
	}

	bool InputSystem::GetMouseButton(int _button) const
	{
		int flag = 0;
		switch (_button)
		{
		case 0:	flag = SDL_BUTTON_LEFT; break;
		case 1: flag = SDL_BUTTON_MIDDLE; break;
		case 2: flag = SDL_BUTTON_RIGHT; break;
		}

		return ((SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(flag)) != 0);
	}
}
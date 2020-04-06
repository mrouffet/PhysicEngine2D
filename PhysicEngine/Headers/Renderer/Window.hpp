#pragma once

#ifndef PE_WINDOW_GUARD
#define PE_WINDOW_GUARD

#include <string>

#include <SDL.h>
#include <GL/glew.h>

namespace Pe
{
	class Vec2;

	class Window
	{
	protected:
		int mWidth = 0;
		int mHeight = 0;

		SDL_Window* mHandleWindow = nullptr;
		SDL_GLContext mHandleContext = nullptr;

	public:
		Window() = default;
		Window(const std::string& _appName, int _width, int _height);

		int GetWidth() const;
		int GetHeight() const;
		float GetRatio() const;
		Vec2 GetDims() const;

		bool Create(const std::string& _appName, int _width, int _height);
		void Destroy();

		void Update();

		void Resize(int _width, int _height);
	};
}

#endif // GUARD
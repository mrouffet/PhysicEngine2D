#include <Core/Debug.hpp>

#include <Maths/Vec2.hpp>

#include <Renderer/Window.hpp>

namespace Pe
{
	Window::Window(const std::string& _appName, int _width, int _height)
	{
		Create(_appName, _width, _height);
	}

	int Window::GetWidth() const
	{
		return mWidth;
	}
	int Window::GetHeight() const
	{
		return mHeight;
	}
	float Window::GetRatio() const
	{
		return (float)mWidth / (float)mHeight;
	}
	Vec2 Window::GetDims() const
	{
		return Vec2(static_cast<float>(mWidth), static_cast<float>(mHeight));
	}

	bool Window::Create(const std::string& _appName, int _width, int _height)
	{
		mWidth = _width;
		mHeight = _height;

		ASSERT(SDL_Init(SDL_INIT_VIDEO) >= 0, "Window::Create(_width, _height): SDL init");

		/* Turn on double buffering with a 24bit Z buffer.
		* You may need to change this to 16 or 32 for your system */
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Init SDL Window
		mHandleWindow = SDL_CreateWindow(
			_appName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			mWidth, mHeight,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
		);


		ASSERT(mHandleWindow, "Window::Create(_width, _height): SDL_CreateWindow");

		// Init Gl Context
		mHandleContext = SDL_GL_CreateContext(mHandleWindow);
		SDL_GL_SetSwapInterval(0);

		ASSERT(mHandleContext, "Window::Create(_width, _height): SDL_GL_CreateContext");


		// Init Glew
		ASSERT(glewInit() == GLEW_OK, "Window::Create(_width, _height): glewInit");

		return true;
	}
	void Window::Destroy()
	{
		SDL_GL_DeleteContext(mHandleContext);
		SDL_DestroyWindow(mHandleWindow);
		SDL_Quit();
	}

	void Window::Update()
	{
		SDL_GL_SwapWindow(mHandleWindow);
	}

	void Window::Resize(int _width, int _height)
	{
		mWidth = _width;
		mHeight = _height;

		glViewport(0, 0, _width, _height);
	}
}
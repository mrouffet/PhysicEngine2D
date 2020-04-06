#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/Behaviors/ScrollScale.hpp>

namespace Pe
{
	float ScrollScale::sStep = 2.27f;


	ScrollScale::ScrollScale(GameObj* _obj) : Component(_obj)
	{
		Engine::GetInputSystem().onMouseWheel = OnWheel;
	}

	void ScrollScale::OnWheel(int scroll)
	{
		Engine::GetRenderSystem().worldScale -= sStep * scroll;
	}
}
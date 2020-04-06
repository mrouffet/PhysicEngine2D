#pragma once

#ifndef PE_SCROLL_SCALE_GUARD
#define PE_SCROLL_SCALE_GUARD

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	class ScrollScale : public Component
	{
		static float sStep;
		static void OnWheel(int scroll);

	public:
		ScrollScale(GameObj* _obj);
	};
}

#endif // GUARD
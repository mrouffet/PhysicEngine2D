#pragma once

#ifndef PE_SCENE_CIRCLES_GUARD
#define PE_SCENE_CIRCLES_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneCircles : public SceneBase
	{
	public:
		SceneCircles(float _worldScale = 50.0f);

		void Create() override final;
	};
}

#endif // GUARD
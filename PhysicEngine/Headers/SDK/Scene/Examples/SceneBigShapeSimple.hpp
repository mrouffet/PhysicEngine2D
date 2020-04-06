#pragma once

#ifndef PE_SCENE_BIG_SHAPE_SIMPLE_GUARD
#define PE_SCENE_BIG_SHAPE_SIMPLE_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneBigShapeSimple : public SceneBase
	{
	public:
		SceneBigShapeSimple(float _worldScale = 50.0f);

		void Create() override final;
	};
}

#endif // GUARD
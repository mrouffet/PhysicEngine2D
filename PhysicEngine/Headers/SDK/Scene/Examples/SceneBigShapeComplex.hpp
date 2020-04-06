#pragma once

#ifndef PE_SCENE_BIG_SHAPE_COMPLEX_GUARD
#define PE_SCENE_BIG_SHAPE_COMPLEX_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneBigShapeComplex : public SceneBase
	{
		unsigned int mPolyCount = 0;

	public:
		SceneBigShapeComplex(unsigned int _polyCount = 25u, float _worldScale = 50.0f);

		void Create() override final;
	};
}

#endif // GUARD
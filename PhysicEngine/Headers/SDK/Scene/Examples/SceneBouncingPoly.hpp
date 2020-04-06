#pragma once

#ifndef PE_SCENE_BOUNCING_POLY_GUARD
#define PE_SCENE_BOUNCING_POLY_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneBouncingPoly : public SceneBase
	{
		const unsigned int mPolyCount = 0;

	public:
		SceneBouncingPoly(unsigned int _polyCount, float _worldScale = 50.0f);

		void Create() override final;
	};
}

#endif // GUARD
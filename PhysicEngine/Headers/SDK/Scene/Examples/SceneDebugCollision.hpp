#pragma once

#ifndef PE_SCENE_DEBUG_COLLISION_GUARD
#define PE_SCENE_DEBUG_COLLISION_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneDebugCollision : public SceneBase
	{
	public:
		SceneDebugCollision(float _worldHeight = 50.0f);

		void Create() override;
	};
}

#endif // GUARD
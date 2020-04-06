#pragma once

#ifndef PE_SCENE_TOWER_GUARD
#define PE_SCENE_TOWER_GUARD

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	class SceneTower : public SceneBase
	{
		const Vec2 mTowerPolyNum;

	public:
		SceneTower(const Vec2& _towerPolyNum = Vec2(5.0f, 15.0f), float _worldScale = 50.0f);

		void Create() override final;
	};
}

#endif // GUARD
#pragma once

#ifndef PE_SCENE_BASE_GUARD
#define PE_SCENE_BASE_GUARD

#include <vector>

#include <SDK/Scene/GameObj.hpp>

namespace Pe
{
	class SceneBase
	{
	protected:
		std::vector<GameObj*> mGameObjs;

		void CreateBorderRectangles();

	public:
		const float worldScale;
		const bool hasBorder;

		SceneBase(float _worldScale = 50.0f, bool _hasBorder = true);

		float GetWorldWidth() const;
		float GetWorldHeight() const;
		float GetWorldScale() const;

		virtual void Create();
		virtual void Destroy();

		GameObj* CreateGameObj(bool _isStatic = false);
	};
}

#endif // GUARD
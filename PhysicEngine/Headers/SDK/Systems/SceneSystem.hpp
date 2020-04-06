#pragma once

#ifndef PE_SCENE_SYSTEM_GUARD
#define PE_SCENE_SYSTEM_GUARD

#include <vector>

#include <SDK/Systems/SystemBase.hpp>
#include <SDK/Systems/Infos/SceneSystemInfos.hpp>

namespace Pe
{
	class SceneSystem : public SystemBase
	{
		unsigned int mCurrentScene = 0;

		std::vector<Component*> mToStartBehaviors;
		std::vector<Component*> mBehaviors;

		void LoadScene(size_t _index);
		void ReloadScene();

		void StartNewComponents();

	public:

		std::function<void(float)> onSetWorldScale = nullptr;

		SceneBase* GetActiveScene() const;

		bool Init() override final;
		void UnInit() override final;

		void Update(float _frameTime) override final;

		void SwitchKey(Key _key) override final;

		void Reset() override final;

		void Register(Component* _behavior) noexcept;
	};
}

#endif // GUARD
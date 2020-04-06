#include <SDK/Engine.hpp>

namespace Pe
{
	SceneBase* SceneSystem::GetActiveScene() const
	{
		return SceneSystemInfos::scenes[mCurrentScene];
	}

	bool SceneSystem::Init()
	{
		if (SceneSystemInfos::scenes.size() <= 0)
			return false;

		if (onSetWorldScale != nullptr)
			onSetWorldScale(SceneSystemInfos::scenes[0]->GetWorldScale());

		SceneSystemInfos::scenes[0]->Create();

		return true;
	}
	void SceneSystem::UnInit()
	{
		Reset();

		SceneSystemInfos::scenes[mCurrentScene]->Destroy();

		for (auto it = SceneSystemInfos::scenes.begin(); it != SceneSystemInfos::scenes.end(); ++it)
			delete *it;

		SceneSystemInfos::scenes.clear();
	}

	void SceneSystem::StartNewComponents()
	{
		for (auto it = mToStartBehaviors.begin(); it != mToStartBehaviors.end(); ++it)
		{
			(*it)->Start();
			mBehaviors.push_back(*it);
		}

		mToStartBehaviors.clear();
	}

	void SceneSystem::Update(float _frameTime)
	{
		sChrono.Start();

		StartNewComponents();

		for (auto it = mBehaviors.begin(); it != mBehaviors.end(); ++it)
			(*it)->Update(_frameTime);

		Debug::DrawText("SceneSystem: " + std::to_string(sChrono.Stop() * 1000.0f) + "ms\n        F3: Reload Scene        F4: Prev Scene        F5: Next Scene");
	}

	void SceneSystem::LoadScene(size_t _index)
	{
		ASSERT(_index < SceneSystemInfos::scenes.size(), "SceneSystem::LoadScene(_index): check Scene index");

		Engine::GetInstance().Reset();
		SceneSystemInfos::scenes[mCurrentScene]->Destroy();

		mCurrentScene = _index;

		if (onSetWorldScale != nullptr)
			onSetWorldScale(SceneSystemInfos::scenes[_index]->GetWorldScale());

		SceneSystemInfos::scenes[_index]->Create();
	}

	void SceneSystem::ReloadScene()
	{
		LoadScene(mCurrentScene);
	}

	void SceneSystem::SwitchKey(Key _key)
	{
		if (_key == Key::K_F3)
		{
			LOG("SceneSystem::SwitchKey(_key): Reload scene", LogLevel::Normal);
			ReloadScene();
		}
		else if (_key == Key::K_F4)
		{
			LOG("SceneSystem::SwitchKey(_key): Load prev scene", LogLevel::Normal);

			if(mCurrentScene == 0)
				LoadScene(SceneSystemInfos::scenes.size() - 1);
			else
				LoadScene(mCurrentScene - 1);
		}
		else if (_key == Key::K_F5)
		{
			LOG("SceneSystem::SwitchKey(_key): Load next scene", LogLevel::Normal);
			LoadScene((mCurrentScene + 1) % SceneSystemInfos::scenes.size());
		}
	}

	void SceneSystem::Reset()
	{
		for (auto it = mBehaviors.begin(); it != mBehaviors.end(); ++it)
			(*it)->End();

		mBehaviors.clear();
		mToStartBehaviors.clear();
	}

	void SceneSystem::Register(Component* _behavior) noexcept
	{
		mToStartBehaviors.push_back(_behavior);
	}
}
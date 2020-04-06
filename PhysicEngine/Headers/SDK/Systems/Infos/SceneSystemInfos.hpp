#pragma once

#ifndef PE_SCENE_SYSTEM_INFOS_GUARD
#define PE_SCENE_SYSTEM_INFOS_GUARD

#include <vector>

#include <SDK/Scene/SceneBase.hpp>

namespace Pe
{
	struct SceneSystemInfos
	{
		static std::vector<SceneBase*> scenes;
	};
}

#endif // GUARD
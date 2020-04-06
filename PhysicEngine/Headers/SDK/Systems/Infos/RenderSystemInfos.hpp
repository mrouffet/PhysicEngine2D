#pragma once

#ifndef PE_RENDER_SYSTEM_INFOS_GUARD
#define PE_RENDER_SYSTEM_INFOS_GUARD

#include <string>

#include <Maths/Vec2.hpp>

namespace Pe
{
	struct RenderSystemInfos
	{
		static std::string appName;
		static Vec2 windowDimention;
	};
}

#endif // GUARD
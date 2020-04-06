#pragma once

#ifndef PE_DRAW_DEBUG_STATE_GUARD
#define PE_DRAW_DEBUG_STATE_GUARD

namespace Pe
{
	enum class DrawDebugState
	{
		None = 0,
		Landmarks =	1,
		RecapLandmarks,
		RecapLandmarksAABB,

		Count
	};
}

#endif // GUARD
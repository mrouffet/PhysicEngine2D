#pragma once

#ifndef PE_FPS_GUARD
#define PE_FPS_GUARD

enum class FPS : unsigned int
{
	Unlocked = 0,
	Locked60,
	Locked30,

	Count,
};

#endif // GUARD
#pragma once

#ifndef PE_FORCE_MODE_GUARD
#define PE_FORCE_MODE_GUARD

namespace Pe
{
	enum class ForceMode
	{
		Force = 0,
		Impulse = 1,
		Acceleration,
		Velocity,
	};
}

#endif // GUARD
#pragma once

#ifndef PE_FORCE_CONSTRAINTS_GUARD
#define PE_FORCE_CONSTRAINTS_GUARD

namespace Pe
{
	enum class ForceConstraints : unsigned int
	{
		FreezeX = 1 << 0,
		FreezeY = 1 << 1,
	};
}

#endif // GUARD
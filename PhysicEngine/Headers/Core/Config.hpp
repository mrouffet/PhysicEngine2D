#pragma once

#ifndef PE_CONFIG_GUARD
#define PE_CONFIG_GUARD

namespace Pe
{
#ifdef PE_DEBUG

	#define PE_LOG 1

	#define PE_ENGINE_SAFE 1

#else

	#define PE_LOG 1

	#define PE_ENGINE_SAFE 0

#endif
}

#endif // GUARD
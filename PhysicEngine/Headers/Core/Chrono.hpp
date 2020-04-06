#pragma once

#ifndef PE_CHRONO_GUARD
#define PE_CHRONO_GUARD

#include <Windows.h>

namespace Pe
{
	class Chrono
	{
		LARGE_INTEGER	mFrequency;
		LARGE_INTEGER	mStartTime;
		LARGE_INTEGER	mStopTime;

	public:
		void Start() noexcept;
		float Stop() noexcept;

		float Restart() noexcept;

		float GetDuration() const;
	};
}

#endif // GUARD
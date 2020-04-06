#include <Core/Chrono.hpp>

namespace Pe
{
	void Chrono::Start() noexcept
	{
		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mStartTime);
	}

	float Chrono::Stop() noexcept
	{
		QueryPerformanceCounter(&mStopTime);

		return GetDuration();
	}
	
	float Chrono::Restart() noexcept
	{
		float duration = Stop();

		Start();

		return duration;
	}

	float Chrono::GetDuration() const
	{
		return (float)(mStopTime.QuadPart - mStartTime.QuadPart) / (float)mFrequency.QuadPart;
	}
}
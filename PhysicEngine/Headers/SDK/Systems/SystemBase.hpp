#pragma once

#ifndef PE_SYSTEM_BASE_GUARD
#define PE_SYSTEM_BASE_GUARD

#include <Core/Key.hpp>

#include <Core/Chrono.hpp>

namespace Pe
{
	class SystemBase
	{
	protected:
		static Chrono sChrono;

	public:
		virtual bool Init() = 0;
		virtual void UnInit() = 0;

		virtual void Update(float _frameTime) = 0;

		virtual void SwitchKey(Key _key) = 0;

		virtual void Reset() = 0;
	};
}

#endif // GUARD
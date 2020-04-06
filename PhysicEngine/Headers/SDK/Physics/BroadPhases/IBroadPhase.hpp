#pragma once

#ifndef PE_IBROAD_PHASE_GUARD
#define PE_IBROAD_PHASE_GUARD

#include <string>
#include <vector>

#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	class IBroadPhase
	{
	public:
		virtual const std::string& GetDebugName() const noexcept = 0;

		virtual void Execute(std::vector<BodyBase*>& _bodies, std::vector<BodyPair>& _broadPhasePairs) noexcept = 0;

		virtual void Reset() noexcept = 0;

		virtual void DrawDebug() noexcept = 0;
	};
}

#endif // GUARD
#pragma once

#ifndef PE_SWEEP_AND_PRUNE_BP_GUARD
#define PE_SWEEP_AND_PRUNE_BP_GUARD

#include <SDK/Physics/BroadPhases/IBroadPhase.hpp>

namespace Pe
{
	class SweepAndPrune_BP : public IBroadPhase
	{
	public:
		const std::string& GetDebugName() const noexcept override final;

		void Execute(std::vector<BodyBase*>& _bodies, std::vector<BodyPair>& _broadPhasePairs) noexcept override final;

		void Reset() noexcept override final;

		virtual void DrawDebug() noexcept override final;
	};
}

#endif // GUARD
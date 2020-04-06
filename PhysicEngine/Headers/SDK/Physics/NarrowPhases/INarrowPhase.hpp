#pragma once

#ifndef PE_INARROW_PHASES_GUARD
#define PE_INARROW_PHASES_GUARD

#include <vector>

#include <SDK/Physics/CollisionInfos.hpp>

namespace Pe
{
	class INarrowPhase
	{
	protected:
		virtual void ComputePair(const BodyPair& _pair, std::vector<CollisionInfos>& _collisions) noexcept = 0;

	public:
		virtual const std::string& GetDebugName() const noexcept = 0;

		virtual void Execute(const std::vector<BodyPair>& _broadPhasePairs, std::vector<CollisionInfos>& _collisions) noexcept;

		virtual void Reset() = 0;

		virtual void DrawDebug() noexcept = 0;
	};
}

#endif // GUARD
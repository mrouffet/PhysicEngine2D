#include <SDK/Physics/NarrowPhases/INarrowPhase.hpp>

namespace Pe
{
	void INarrowPhase::Execute(const std::vector<BodyPair>& _broadPhasePairs, std::vector<CollisionInfos>& _collisions) noexcept
	{
		for (auto it = _broadPhasePairs.begin(); it != _broadPhasePairs.end(); ++it)
			ComputePair(*it, _collisions);
	}
}
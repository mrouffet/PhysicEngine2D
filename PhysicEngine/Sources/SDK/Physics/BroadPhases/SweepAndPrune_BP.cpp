#include <algorithm>

#include <Core/Debug.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Physics/BroadPhases/SweepAndPrune_BP.hpp>

namespace Pe
{
	struct BodyXComparer
	{
		bool operator()(const BodyBase* _lhs, const BodyBase* _rhs) noexcept
		{
			return _lhs->aabb->min.x < _rhs->aabb->min.x;
		}
	};

	const std::string& SweepAndPrune_BP::GetDebugName() const noexcept
	{
		static const std::string sDebugName = "SweepAndPrune";
		return sDebugName;
	}

	void SweepAndPrune_BP::Execute(std::vector<BodyBase*>& _bodies, std::vector<BodyPair>& _pairs) noexcept
	{
		// Sort bodies by axis.
		std::sort(_bodies.begin(), _bodies.end(), BodyXComparer());

		for (auto it = _bodies.begin(); it != _bodies.end(); ++it)
		{
			// cache.
			float maxX = (*it)->aabb->max.x;
			float minY = (*it)->aabb->min.y;
			float maxY = (*it)->aabb->max.y;
			bool isStatic = (*it)->IsStatic();

			for (auto it2 = it + 1; it2 != _bodies.end(); ++it2)
			{
				if ((*it2)->aabb->min.x > maxX)
					break;

				// Check both static or out of Y bound.
				if (isStatic && (*it2)->IsStatic() || minY > (*it2)->aabb->max.y || maxY < (*it2)->aabb->min.y)
					continue;

				_pairs.push_back(BodyPair(*it, *it2));
			}
		}
	}

	void SweepAndPrune_BP::Reset() noexcept
	{
	}

	void SweepAndPrune_BP::DrawDebug() noexcept
	{
	}
}
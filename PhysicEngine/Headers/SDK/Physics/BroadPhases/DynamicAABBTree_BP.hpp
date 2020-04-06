#pragma once

#ifndef PE_DYNAMIC_AABB_TREE_BP_GUARD
#define PE_DYNAMIC_AABB_TREE_BP_GUARD

#include <SDK/Physics/BroadPhases/IBroadPhase.hpp>
#include <SDK/Physics/BroadPhases/DynamicAABBTree.hpp>

namespace Pe
{
	class DynamicAABBTree_BP : public IBroadPhase
	{
		DynamicAABBTree mTree;

		void DrawNode(const DynamicAABBTree::Node* _node) noexcept;

	public:
		const std::string& GetDebugName() const noexcept override final;

		void Execute(std::vector<BodyBase*>& _bodies, std::vector<BodyPair>& _broadPhasePairs) noexcept override final;

		void Reset() noexcept override final;

		void DrawDebug() noexcept override final;
	};
}

#endif // GUARD
#include <SDK/Engine.hpp>

#include <SDK/Physics/BroadPhases/DynamicAABBTree_BP.hpp>

namespace Pe
{
	const std::string& DynamicAABBTree_BP::GetDebugName() const noexcept
	{
		static const std::string sDebugName = "DynamicAABBTree";
		return sDebugName;
	}

	void DynamicAABBTree_BP::Execute(std::vector<BodyBase*>& _bodies, std::vector<BodyPair>& _pairs) noexcept
	{
		mTree.Clear();

		for (auto it = _bodies.begin(); it != _bodies.end(); ++it)
			mTree.Add(*it);

		mTree.Query(_pairs);
	}

	void DynamicAABBTree_BP::DrawDebug() noexcept
	{
		const DynamicAABBTree::Node* root = mTree.GetRoot();

		if (root == nullptr)
			return;

		DrawNode(root);
	}

	void DynamicAABBTree_BP::DrawNode(const DynamicAABBTree::Node* _node) noexcept
	{
		if (!_node->isLeaf)
		{
			Debug::DrawRectangle(_node->branch.aabb, Color{ 0.75f, 0.0f, 0.0f });

			DrawNode(_node->branch.lChild);
			DrawNode(_node->branch.rChild);
		}
	}

	void DynamicAABBTree_BP::Reset() noexcept
	{
		mTree.Clear();
	}
}
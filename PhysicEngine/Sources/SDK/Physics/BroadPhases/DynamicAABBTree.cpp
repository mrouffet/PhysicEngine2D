#include <Maths/Algorithms.hpp>

#include <SDK/Physics/BroadPhases/DynamicAABBTree.hpp>

namespace Pe
{
	// === Node ===
	DynamicAABBTree::Node::Node(Leaf&& _leaf) noexcept :
		isLeaf{ true },
		leaf{ std::move(_leaf) }
	{
	}
	DynamicAABBTree::Node::Node(Branch&& _branch) noexcept :
		isLeaf{ false },
		branch{ std::move(_branch) }
	{
	}
	DynamicAABBTree::Node::~Node()
	{
		if (isLeaf)
			leaf.~Leaf();
		else
			branch.~Branch();
	}

	const AABB& DynamicAABBTree::Node::GetGeometry() const noexcept
	{
		return isLeaf ? *leaf.body->aabb : branch.aabb;
	}


	// === Branch ===
	DynamicAABBTree::Branch::Branch(Branch* _parent, Node* _lChild, Node* _rChild) noexcept :
		parent{ _parent },
		lChild{ _lChild },
		rChild{ _rChild }
	{
		// Must be call manually after assignation.
		//ComputeAABB();
	}
	DynamicAABBTree::Branch::Branch(Branch&& _other) noexcept :
		aabb{ _other.aabb },
		parent{ _other.parent },
		lChild{ _other.lChild },
		rChild{ _other.rChild }
	{
		_other.lChild = nullptr;
		_other.rChild = nullptr;
	}

	DynamicAABBTree::Branch::~Branch()
	{
		delete lChild;
		delete rChild;
	}

	const AABB& DynamicAABBTree::Branch::GetGeometry() const noexcept
	{
		return aabb;
	}

	void DynamicAABBTree::Branch::ComputeAABB() noexcept
	{
		aabb = AABB(lChild->GetGeometry(), rChild->GetGeometry());

		if (parent)
			parent->ComputeAABB();
	}


	// === Leaf ===
	DynamicAABBTree::Leaf::Leaf(BodyBase* _body) noexcept : body{ _body }
	{
	}

	const AABB& DynamicAABBTree::Leaf::GetGeometry() const noexcept
	{
		return *body->aabb;
	}


	// === Tree ===
	const DynamicAABBTree::Node* DynamicAABBTree::GetRoot() const noexcept
	{
		return mRoot;
	}

	void DynamicAABBTree::Add(BodyBase* _body) noexcept
	{
		if (!mRoot)
		{
			mRoot = new Node(_body);
			return;
		}


		// Find.
		float bodyArea = _body->aabb->ComputeArea();

		Branch* prevIt = nullptr;
		Node* it = mRoot;

		float bodyLChildArea = 0.0f;
		float bodyRChildArea = 0.0f;
		float LRChildArea = 0.0f;

		while (!it->isLeaf) // Arrived at end.
		{
			Branch& branch = it->branch;

			bodyLChildArea = AABB(*_body->aabb, branch.lChild->GetGeometry()).ComputeArea();
			bodyRChildArea = AABB(*_body->aabb, branch.rChild->GetGeometry()).ComputeArea();
			LRChildArea = branch.aabb.ComputeArea();

			if (bodyLChildArea < LRChildArea)
				it = bodyLChildArea < bodyRChildArea ? branch.lChild : branch.rChild;
			else if (bodyRChildArea < LRChildArea)
				it = bodyLChildArea < bodyRChildArea ? branch.lChild : branch.rChild;
			else
				break; // pair clother to new body.

			prevIt = &branch;
		}


		// Insert.

		// New Root.
		if (prevIt == nullptr)
		{
			mRoot = new Node(Branch(nullptr, mRoot, new Node(_body)));
			mRoot->branch.ComputeAABB();
			return;
		}

		if (it == prevIt->lChild)
		{
			prevIt->lChild = new Node(Branch(prevIt, prevIt->lChild, new Node(_body)));
			prevIt->lChild->branch.ComputeAABB();
		}
		else
		{
			prevIt->rChild = new Node(Branch(prevIt, prevIt->rChild, new Node(_body)));
			prevIt->rChild->branch.ComputeAABB();
		}
	}
	void DynamicAABBTree::Clear() noexcept
	{
		if (!mRoot)
			return;

		delete mRoot;
		mRoot = nullptr;
	}

	void DynamicAABBTree::Query(std::vector<BodyPair>& _pairs) const noexcept
	{
		if (!mRoot)
			return;

		QueryNode(mRoot, _pairs);
	}

	void DynamicAABBTree::QueryNode(Node* _node, std::vector<BodyPair>& _pairs) const noexcept
	{
		if (!_node->isLeaf)
			QueryBranch(_node->branch, _pairs);
	}

	void DynamicAABBTree::QueryBranch(const Branch& _branch, std::vector<BodyPair>& _pairs) const noexcept
	{
		if (!_branch.lChild->isLeaf)
			QueryBranch(_branch.lChild->branch, _pairs);

		if (!_branch.rChild->isLeaf)
			QueryBranch(_branch.rChild->branch, _pairs);


		// Check no collision.
		if (!_branch.lChild->GetGeometry().IsColliding(_branch.rChild->GetGeometry()))
			return;

		if (_branch.lChild->isLeaf)
		{
			if (_branch.rChild->isLeaf)
				_pairs.push_back(BodyPair(_branch.lChild->leaf.body, _branch.rChild->leaf.body));
			else
				QueryLeafPairs(_branch.lChild->leaf, _branch.rChild->branch, _pairs);
		}
		else if (_branch.rChild->isLeaf)
			QueryLeafPairs(_branch.rChild->leaf, _branch.lChild->branch, _pairs);
		else
			QueryBranchPairs(_branch.lChild->branch, _branch.rChild->branch, _pairs);
	}

	void DynamicAABBTree::QueryLeafPairs(const Leaf& _leaf, const Branch& _branch, std::vector<BodyPair>& _pairs) const noexcept
	{
		// Left Child.
		if (_leaf.GetGeometry().IsColliding(_branch.lChild->GetGeometry()))			// Check collision.
		{
			if (_branch.lChild->isLeaf)												// Leaf type.
				_pairs.push_back(BodyPair(_leaf.body, _branch.lChild->leaf.body));
			else
				QueryLeafPairs(_leaf, _branch.lChild->branch, _pairs);				// Branch type.
		}


		// Right Child.
		if (_leaf.GetGeometry().IsColliding(_branch.rChild->GetGeometry()))			// Check collision.
		{
			if (_branch.rChild->isLeaf)												// Leaf type.
				_pairs.push_back(BodyPair(_leaf.body, _branch.rChild->leaf.body));
			else
				QueryLeafPairs(_leaf, _branch.rChild->branch, _pairs);				// Branch type.
		}
	}

	void DynamicAABBTree::QueryBranchPairs(const Branch& _branch1, const Branch& _branch2, std::vector<BodyPair>& _pairs) const noexcept
	{
		// Left Child.
		if (_branch1.lChild->GetGeometry().IsColliding(_branch2.GetGeometry()))			// Check collision.
		{
			if (_branch1.lChild->isLeaf)												// Leaf type.
				QueryLeafPairs(_branch1.lChild->leaf, _branch2, _pairs);
			else
				QueryBranchPairs(_branch1.lChild->branch, _branch2, _pairs);			// Branch type.
		}


		// Right Child.
		if (_branch1.rChild->GetGeometry().IsColliding(_branch2.GetGeometry()))			// Check collision.
		{
			if (_branch1.rChild->isLeaf)												// Leaf type.
				QueryLeafPairs(_branch1.rChild->leaf, _branch2, _pairs);
			else
				QueryBranchPairs(_branch1.rChild->branch, _branch2, _pairs);			// Branch type.
		}
	}
}
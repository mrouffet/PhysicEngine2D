#pragma once

#ifndef PE_DYNAMIC_AABB_TREE_GUARD
#define PE_DYNAMIC_AABB_TREE_GUARD

#include <vector>

#include <Maths/AABB.hpp>

#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	class DynamicAABBTree
	{
	public:
		struct Node;

		struct Branch
		{
			AABB aabb;

			Branch* parent;

			Node* lChild = nullptr;
			Node* rChild = nullptr;

			Branch(Branch* _parent, Node* _lChild, Node* _rChild) noexcept;
			Branch(Branch&& _other) noexcept;
			Branch(const Branch&) = delete;
			~Branch();

			const AABB& GetGeometry() const noexcept;

			void ComputeAABB() noexcept;
		};

		struct Leaf
		{
			BodyBase* const body;

			Leaf(BodyBase* _body) noexcept;

			const AABB& GetGeometry() const noexcept;
		};

		struct Node
		{
			union
			{
				Leaf leaf;
				Branch branch;
			};

			const bool isLeaf = true;

			Node(Leaf&& _leaf) noexcept;
			Node(Branch&& _branch) noexcept;
			~Node();

			const AABB& GetGeometry() const noexcept;
		};

	private:
		Node* mRoot = nullptr;

		void QueryNode(Node* _node, std::vector<BodyPair>& _pairs) const noexcept;
		void QueryBranch(const Branch& _branch, std::vector<BodyPair>& _pairs) const noexcept;
		void QueryLeafPairs(const Leaf& _leaf, const Branch& _branch, std::vector<BodyPair>& _pairs) const noexcept;
		void QueryBranchPairs(const Branch& _branch1, const Branch& _branch2, std::vector<BodyPair>& _pairs) const noexcept;

	public:
		const Node* GetRoot() const noexcept;

		void Add(BodyBase* _body) noexcept;
		void Clear() noexcept;

		void Query(std::vector<BodyPair>& _pairs) const noexcept;
	};
}

#endif // GUARD
#pragma once

#ifndef PE_PHYSIC_SYSTEM_INFOS_GUARD
#define PE_PHYSIC_SYSTEM_INFOS_GUARD

#include <vector>

#include <Physics/Forces/ForceInfos.hpp>

#include <SDK/Physics/BroadPhases/SweepAndPrune_BP.hpp>
#include <SDK/Physics/BroadPhases/DynamicAABBTree_BP.hpp>

#include <SDK/Physics/NarrowPhases/SAT_NP.hpp>
#include <SDK/Physics/NarrowPhases/GJK_NP.hpp>

namespace Pe
{
	struct PhysicSystemInfos
	{
	public:
		static float fixedTime;

		static ForceInfos gravityInfos;

		static std::vector<IBroadPhase*> broadPhases;
		static std::vector<INarrowPhase*> narrowPhases;

		static void ResetGravity();
	};
}

#endif // GUARD
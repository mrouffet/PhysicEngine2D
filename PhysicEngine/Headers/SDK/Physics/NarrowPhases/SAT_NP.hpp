#pragma once

#ifndef PE_SAT_NP_GUARD
#define PE_SAT_NP_GUARD

#include <SDK/Physics/NarrowPhases/INarrowPhase.hpp>

namespace Pe
{
	class SAT_NP : public INarrowPhase
	{
		struct ComputeShapeInfos
		{
			Vec2 normal;
			Vec2 point;

			float penetration = FLT_MAX;

			bool dirtyFlag = false;
		};

		struct ComputeProjectionInfos
		{
			Vec2 min; // Vertex min.
			Vec2 max; // Vertex max.

			Vec2 proj = Vec2(FLT_MAX, -FLT_MAX); // {pMin, pMax}.
		};

		void ComputePair(const BodyPair& _pair, std::vector<CollisionInfos>& _collisions) noexcept override final;
		bool ComputeShape(const std::vector<Vec2>& _fWorldShape, const std::vector<Vec2>& _sWorldShape, ComputeShapeInfos& _computeInfos);
		ComputeProjectionInfos ComputeProjection(const Vec2& _normal, const std::vector<Vec2>& _worldShape);

	public:
		const std::string& GetDebugName() const noexcept override final;

		void Reset() noexcept override final;

		void DrawDebug() noexcept override final;
	};
}

#endif // GUARD
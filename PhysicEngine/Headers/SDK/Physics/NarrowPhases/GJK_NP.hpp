#pragma once

#ifndef PE_GJK_NP_GUARD
#define PE_GJK_NP_GUARD

#include <SDK/Physics/NarrowPhases/INarrowPhase.hpp>

namespace Pe
{
	class GJK_NP : public INarrowPhase
	{
		struct SupportInfos : public Vec2
		{
			Vec2 fPoint;
			Vec2 sPoint;

			SupportInfos(const Vec2& _support, const Vec2&_fPoint, const Vec2& _sPoint) :
				Vec2(_support),
				fPoint{ _fPoint },
				sPoint{ _sPoint }
			{
			}
		};

		// Save vector for memory allocation.
		std::vector<SupportInfos> mSimplex;

		void ComputePair(const BodyPair& _pair, std::vector<CollisionInfos>& _collisions) noexcept override final;

		Vec2 ComputeClosestPointToOrigin(const Vec2& _pointA, const Vec2& _pointB) const noexcept;
		Vec2 ComputeClosestPointToOrigin(unsigned int _size) const noexcept;
		Vec2 ComputeClosestPointToOrigin(unsigned int _size, int& closestIndex) const noexcept;

		Vec2 Support(const std::vector<Vec2>& _points, const Vec2& _dir) noexcept;
		SupportInfos Support(const std::vector<Vec2>& _fShape, const std::vector<Vec2>& _sShape, const Vec2& _dir) noexcept;

	public:
		GJK_NP();

		const std::string& GetDebugName() const noexcept override final;

		void Reset() noexcept override final;

		void DrawDebug() noexcept override final;
	};
}

#endif // GUARD
#include <Maths/Algorithms.hpp>

#include <SDK/Engine.hpp>

#include <SDK/Physics/NarrowPhases/SAT_NP.hpp>

namespace Pe
{
	const std::string& SAT_NP::GetDebugName() const noexcept
	{
		static const std::string sDebugName = "SAT";
		return sDebugName;
	}

	void SAT_NP::ComputePair(const BodyPair& _pair, std::vector<CollisionInfos>& _collisions) noexcept
	{
		ComputeShapeInfos computeInfos;

		const std::vector<Vec2>& fWorldShape = _pair.first->GetShape()->GetPoints();
		const std::vector<Vec2>& sWorldShape = _pair.second->GetShape()->GetPoints();

		if (!ComputeShape(fWorldShape, sWorldShape, computeInfos))
			return;

		// Identify order: which one is piercing the other.
		computeInfos.dirtyFlag = false;

		if (ComputeShape(sWorldShape, fWorldShape, computeInfos))
		{
#if SAT_DEBUG
			// Draw collision normal.
			Debug::DrawLine(
				Vec2(0.0f, 0.0f),
				computeInfos.normal,
				Color{ 0.75f, 0.75f, 0.0f }
			);

			// Draw point + penetration.
			Debug::DrawLine(
				computeInfos.point,
				computeInfos.point + computeInfos.normal * -computeInfos.penetration
			);
#endif

			CollisionInfos collisionInfos(computeInfos.dirtyFlag ? _pair : _pair.GetReversed());
			collisionInfos.collisionPoints.push_back(CollisionPointInfos{ computeInfos.normal, computeInfos.point, computeInfos.penetration });
			
			_collisions.push_back(collisionInfos);
		}
	}

	bool SAT_NP::ComputeShape(const std::vector<Vec2>& _fWorldShape, const std::vector<Vec2>& _sWorldShape, ComputeShapeInfos& _computeInfos)
	{
		Vec2 currPoint;
		Vec2 nextPoint = _fWorldShape[0];

		ComputeProjectionInfos fProjInfos;
		ComputeProjectionInfos sProjInfos;

		// For each normal of _fWorldShape.
		for (unsigned int i = 0; i < _fWorldShape.size(); ++i)
		{
			currPoint = nextPoint;
			nextPoint = _fWorldShape[(i + 1) % _fWorldShape.size()];

			Vec2 normal = (currPoint - nextPoint).GetNormal().GetNormalized();

#if SAT_DEBUG
			// Draw shape's edge normal.
			Debug::DrawLine(
				(currPoint + nextPoint) / 2.0f,
				(currPoint + nextPoint) / 2.0f + normal,
				Color{ 0.75f, 0.0f, 0.0f }
			);
#endif

			fProjInfos = ComputeProjection(normal, _fWorldShape);
			sProjInfos = ComputeProjection(normal, _sWorldShape);

			if (fProjInfos.proj.x > sProjInfos.proj.y || fProjInfos.proj.y < sProjInfos.proj.x)
				return false;

			// overlap = projDist - diff between 2 shape.
			float penetration = Algo::Abs(fProjInfos.proj.y - sProjInfos.proj.x);

			if (penetration < _computeInfos.penetration)
				_computeInfos = ComputeShapeInfos{ normal, sProjInfos.min + normal * penetration, penetration, true };
		}

		return true;
	}

	SAT_NP::ComputeProjectionInfos SAT_NP::ComputeProjection(const Vec2& _normal, const std::vector<Vec2>& _worldShape)
	{
		ComputeProjectionInfos ProjInfos;

		for (auto it = _worldShape.begin(); it != _worldShape.end(); ++it)
		{
			float dot = _normal.Dot(*it);

			if (ProjInfos.proj.x > dot)
			{
				ProjInfos.proj.x = dot;
				ProjInfos.min = *it;
			}

			if (ProjInfos.proj.y < dot)
			{
				ProjInfos.proj.y = dot;
				ProjInfos.max = *it;
			}
		}

		return ProjInfos;
	}

	void SAT_NP::Reset() noexcept
	{
	}

	void SAT_NP::DrawDebug() noexcept
	{
	}
}
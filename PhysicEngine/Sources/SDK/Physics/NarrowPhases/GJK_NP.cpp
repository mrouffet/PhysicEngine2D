#include <algorithm>

#include <Maths/Hull.hpp>
#include <Maths/Algorithms.hpp>
#include <Maths/Shapes/Triangle.hpp>

#include <SDK/Miscs/Config.hpp>

#include <SDK/Physics/NarrowPhases/GJK_NP.hpp>

#if GJK_DEBUG
#include <SDK/Engine.hpp>
#endif

namespace Pe
{
	GJK_NP::GJK_NP()
	{
		mSimplex.reserve(5u); // Reserve maximum size.
	}

	const std::string& GJK_NP::GetDebugName() const noexcept
	{
		static const std::string sDebugName = "GJK";
		return sDebugName;
	}

	void GJK_NP::ComputePair(const BodyPair& _pair, std::vector<CollisionInfos>& _collisions) noexcept
	{
		const std::vector<Vec2>& fWorldShape = _pair.first->GetShape()->GetPoints();
		const std::vector<Vec2>& sWorldShape = _pair.second->GetShape()->GetPoints();

#if GJK_DEBUG
		if (Engine::GJK_INDEX != 0)
		{
			std::vector<Vec2> minkowski;
			minkowski.reserve(fWorldShape.size() * sWorldShape.size());

			for (auto fIt = fWorldShape.begin(); fIt != fWorldShape.end(); ++fIt)
			{
				for (auto sIt = sWorldShape.begin(); sIt != sWorldShape.end(); ++sIt)
					minkowski.push_back(*fIt - *sIt);
			}

			// Draw full
			for (unsigned int i = 0; i < minkowski.size(); ++i)
			{
				for (unsigned int j = i; j < minkowski.size(); ++j)
					Debug::DrawLine(minkowski[i], minkowski[j], Color{ 0.15f, 0.25f, 0.15f });
			}


			// Graham Scan: https://en.wikipedia.org/wiki/Graham_scan

			// find lowest X point.
			Vec2 lowPoint = minkowski.front();
			for (auto it = minkowski.begin(); it != minkowski.end(); ++it)
			{
				if (it->x < lowPoint.x)
					lowPoint = *it;
				else if (Algo::NearlyEqual(it->x, lowPoint.x) && it->y < lowPoint.y)
					lowPoint = *it;
			}

			// Sort by Slope.
			struct SlopeComparer
			{
				const Vec2& point;

				SlopeComparer(const Vec2& _point) : point{ _point }
				{
				}

				bool operator()(const Vec2& _lhs, const Vec2& _rhs) noexcept
				{
					if (_rhs == point)
						return false;
					if (_lhs == point)
						return true;

					return (_lhs - point).GetSlope() < (_rhs - point).GetSlope();
				}
			};

			std::sort(minkowski.begin(), minkowski.end(), SlopeComparer(lowPoint));

			// begin() + 2: Start with 2 points.
			for (auto it = minkowski.begin() + 2; it != minkowski.end(); ++it)
			{
				auto rIt = it - 1;

				while (rIt != minkowski.begin())
				{
					auto prevRIt = rIt - 1;

					// Simplified double cross: (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
					float sign = (rIt->x - prevRIt->x) * (it->y - prevRIt->y) - (rIt->y - prevRIt->y) * (it->x - prevRIt->x);

					// Clock-wises sign: stop erasing.
					if (sign > 0.0f)
						break;

					rIt--;
				}

				// Erase all non clock-wise segments.
				if (rIt != it - 1)
					it = minkowski.erase(rIt + 1, it) - 1;
			}


			// Draw hull.
			for (unsigned int i = 0; i < minkowski.size(); ++i)
				Debug::DrawLine(minkowski[i], minkowski[(i + 1) % minkowski.size()], Color{ 0.25f, 0.75f, 0.75f });
		}
#endif
		mSimplex.clear();

		// Start with 2 opposite points.
		mSimplex.push_back(Support(fWorldShape, sWorldShape, Vec2(-1.0f, 0.0f)));
		mSimplex.push_back(Support(fWorldShape, sWorldShape, -mSimplex[0]));

#if GJK_DEBUG
		if (Engine::GJK_INDEX == 1)
		{
			Debug::DrawLine(Vec2(), mSimplex[0], Color{ 1.0f, 0.0f, 1.0f });
			Debug::DrawLine(Vec2(), -mSimplex[0], Color{ 0.5f, 1.0f, 0.5f });
		}

		if (Engine::GJK_INDEX == 2)
		{
			Debug::DrawLine(mSimplex[0], mSimplex[1], Color{ 1.0f, 1.0f, 0.0f });

			Debug::DrawLine(Vec2(), mSimplex[0], Color{ 1.0f, 0.0f, 1.0f });
			Debug::DrawLine(Vec2(), -mSimplex[0], Color{ 0.5f, 1.0f, 0.5f });
		}
#endif

		Vec2 closest = ComputeClosestPointToOrigin(mSimplex[0], mSimplex[1]);

#if GJK_DEBUG
		if (Engine::GJK_INDEX == 3)
		{
			Debug::DrawLine(mSimplex[0], mSimplex[1], Color{ 1.0f, 1.0f, 0.0f });

			Debug::DrawLine(Vec2(), closest, Color{ 1.0f, 0.0f, 1.0f });
			Debug::DrawLine(Vec2(), -closest, Color{ 0.5f, 1.0f, 0.5f });
		}
#endif

		mSimplex.push_back(Support(fWorldShape, sWorldShape, -closest));

#if GJK_DEBUG
		if (Engine::GJK_INDEX == 4)
		{
			for (unsigned int i = 0u; i < 3u; ++i)
				Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % 3u], Color{ 1.0f, 1.0f, 0.0f });

			Debug::DrawLine(Vec2(), closest, Color{ 1.0f, 0.0f, 1.0f });
			Debug::DrawLine(Vec2(), -closest, Color{ 0.5f, 1.0f, 0.5f });
		}

		unsigned int debIndex = 4;
#endif
		int closestIndex = -1;

		while (true)
		{
			Vec2 newClosest = ComputeClosestPointToOrigin(3u, closestIndex);

			// Same closest: GJK triangle found.
			if (newClosest == closest)
				break;

			closest = newClosest;

#if GJK_DEBUG
			if (++debIndex == Engine::GJK_INDEX)
			{
				for (unsigned int i = 0u; i < 3u; ++i)
					Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % 3], Color{ 1.0f, 1.0f, 0.0f });

				Debug::DrawLine(Vec2(), closest, Color{ 1.0f, 0.0f, 1.0f });
				Debug::DrawLine(Vec2(), -closest, Color{ 0.5f, 1.0f, 0.5f });
			}
#endif
			mSimplex[(closestIndex + 2) % 3u] = Support(fWorldShape, sWorldShape, -closest);

#if GJK_DEBUG
			if (++debIndex == Engine::GJK_INDEX)
			{
				for (unsigned int i = 0u; i < 3u; ++i)
					Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % 3], Color{ 1.0f, 1.0f, 0.0f });

				Debug::DrawLine(Vec2(), closest, Color{ 1.0f, 0.0f, 1.0f });
				Debug::DrawLine(Vec2(), -closest, Color{ 0.5f, 1.0f, 0.5f });
			}
#endif
		}

#if GJK_DEBUG
		if (Engine::GJK_INDEX == ++debIndex)
		{
			for (unsigned int i = 0; i < 3u; ++i)
				Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % 3u], Color{ 1.0f, 0.3f, 0.3f });

			Debug::DrawLine(Vec2(), closest, Color{ 1.0f, 0.0f, 1.0f });
			Debug::DrawLine(Vec2(), -closest, Color{ 0.5f, 1.0f, 0.5f });
		}
#endif

		// origin not in GJK mSimplex: no collision.
		Vec2 triangle[] = { mSimplex[0], mSimplex[1], mSimplex[2] };
		if (!Triangle::IsPointIn(triangle, Vec2()))
		{
#if GJK_DEBUG
			if (Engine::GJK_INDEX > ++debIndex)
				Engine::GJK_INDEX = 0u;
#endif

			return;
		}

		mSimplex.push_back(Support(fWorldShape, sWorldShape, closest)); // Add new point: use same sign as the closest.

		Hull::Create(mSimplex); // Create hull: avoid bad segments origin check.

#if GJK_DEBUG
		if (Engine::GJK_INDEX == ++debIndex)
		{
			for (unsigned int i = 0; i < mSimplex.size(); ++i)
				Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % mSimplex.size()], Color{ 1.0f, 0.3f, 0.3f });

			Debug::DrawLine(Vec2(), closest, Color{ 0.5f, 1.0f, 0.5f });
		}
#endif

		closest = ComputeClosestPointToOrigin(4u);
		mSimplex.push_back(Support(fWorldShape, sWorldShape, closest)); // Add new point: use same sign as the closest.

		Hull::Create(mSimplex); // Create hull: avoid bad segments origin check.

#if GJK_DEBUG
		if (Engine::GJK_INDEX == ++debIndex)
		{
			for (unsigned int i = 0; i < mSimplex.size(); ++i)
				Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % mSimplex.size()], Color{ 1.0f, 0.3f, 0.3f });

			Debug::DrawLine(Vec2(), closest, Color{ 0.5f, 1.0f, 0.5f });
		}
#endif

		// Compute new closest and query closestIndex.
		closest = ComputeClosestPointToOrigin(mSimplex.size(), closestIndex);

		// Get the hull's edge closest to origin.
		Vec2 closestEdge = mSimplex[(closestIndex + 1) % mSimplex.size()] - mSimplex[closestIndex];

		// Compute collision point.
		float dot = (closest - mSimplex[closestIndex]).Dot(closestEdge) / closestEdge.Dot(closestEdge);

		Vec2 collisionPoint = mSimplex[closestIndex].sPoint + (mSimplex[(closestIndex + 1) % mSimplex.size()].sPoint - mSimplex[closestIndex].sPoint) * dot;
		//Vec2 collisionPoint = mSimplex[closestIndex].fPoint + (mSimplex[(closestIndex + 1) % mSimplex.size()].fPoint - mSimplex[closestIndex].fPoint) * dot;

		// normal == -closest.
		CollisionInfos collisionInfos(_pair);
		collisionInfos.collisionPoints.push_back(CollisionPointInfos{ -closest.GetNormalized(), collisionPoint, closest.GetNorm() });

		_collisions.push_back(collisionInfos);

#if GJK_DEBUG
		if (Engine::GJK_INDEX == ++debIndex)
		{
			for (unsigned int i = 0; i < mSimplex.size(); ++i)
				Debug::DrawLine(mSimplex[i], mSimplex[(i + 1) % mSimplex.size()], Color{ 0.3f, 0.3f, 1.0f });

			Debug::DrawLine(Vec2(), closest, Color{ 0.5f, 1.0f, 0.5f });
			Debug::DrawLine(Vec2(), -closest, Color{ 1.0f, 1.0f, 0.0f });
		}
		else if (Engine::GJK_INDEX > ++debIndex)
			Engine::GJK_INDEX = 0u;
#endif
	}


	Vec2 GJK_NP::ComputeClosestPointToOrigin(const Vec2& _pointA, const Vec2& _pointB) const noexcept
	{
		Vec2 AB = (_pointB - _pointA).GetNormalized();
		return _pointA - AB * AB.Dot(_pointA);
	}
	Vec2 GJK_NP::ComputeClosestPointToOrigin(unsigned int _size) const noexcept
	{
		float closestSqrNorm = FLT_MAX;

		Vec2 closest;
		Vec2 newPoint;
		float newPointSqrNorm = 0.0f;

		for (unsigned int i = 0; i < _size; ++i)
		{
			newPoint = ComputeClosestPointToOrigin(mSimplex[i], mSimplex[(i + 1) % _size]);
			newPointSqrNorm = newPoint.GetSqrNorm();

			if (newPointSqrNorm < closestSqrNorm)
			{
				closestSqrNorm = newPointSqrNorm;
				closest = newPoint;
			}
		}

		return closest;
	}
	Vec2 GJK_NP::ComputeClosestPointToOrigin(unsigned int _size, int& closestIndex) const noexcept
	{
		float closestSqrNorm = FLT_MAX;
		closestIndex = -1;

		Vec2 closest;
		Vec2 newPoint;
		float newPointSqrNorm = 0.0f;

		for (unsigned int i = 0; i < _size; ++i)
		{
			newPoint = ComputeClosestPointToOrigin(mSimplex[i], mSimplex[(i + 1) % _size]);
			newPointSqrNorm = newPoint.GetSqrNorm();

			if (newPointSqrNorm < closestSqrNorm)
			{
				closestSqrNorm = newPointSqrNorm;
				closestIndex = i;

				closest = newPoint;
			}
		}

		return closest;
	}

	Vec2 GJK_NP::Support(const std::vector<Vec2>& _points, const Vec2& _dir) noexcept
	{
		// Return the point in _points with the highest dot of _dir.

		float maxDot = -FLT_MAX;
		Vec2 maxPoint;

		for (auto it = _points.begin(); it != _points.end(); ++it)
		{
			float dot = _dir.Dot(*it);

			if (dot >= maxDot)
			{
				maxDot = dot;
				maxPoint = *it;
			}
		}

		return maxPoint;
	}
	GJK_NP::SupportInfos GJK_NP::Support(const std::vector<Vec2>& _fShape, const std::vector<Vec2>& _sShape, const Vec2& _dir) noexcept
	{
		Vec2 fPoint = Support(_fShape, _dir);
		Vec2 sPoint = Support(_sShape, -_dir);

		return SupportInfos{ fPoint - sPoint, fPoint , sPoint };
	}

	void GJK_NP::Reset() noexcept
	{
	}

	void GJK_NP::DrawDebug() noexcept
	{
	}
}
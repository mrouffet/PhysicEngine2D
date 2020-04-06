#pragma once

#ifndef PE_FORCE_INFOS_GUARD
#define PE_FORCE_INFOS_GUARD

#include <Maths/Vec2.hpp>

#include <Physics/Forces/ForceMode.hpp>
#include <Physics/Forces/MotionMode.hpp>

namespace Pe
{
	struct ForceInfos
	{
		Vec2 force = Vec2();
		Vec2 localPoint = Vec2();
		ForceMode forceMode = ForceMode::Force;

		ForceInfos(Vec2 _force, ForceMode _forceMode = ForceMode::Force, Vec2 _localPoint = Vec2()) :
			force{ _force },
			localPoint{ _localPoint },
			forceMode{ _forceMode }
		{
		}
	};

	struct ForceParams : public ForceInfos
	{
		MotionMode motionMode = MotionMode::Linear;
		bool shouldNormalize = false;

		ForceParams(Vec2 _force, ForceMode _forceMode = ForceMode::Force, MotionMode _motionMode = MotionMode::Linear, Vec2 _localPoint = Vec2(), bool _shouldNormalize = false) :
			ForceInfos(_force, _forceMode, _localPoint),
			motionMode{ _motionMode },
			shouldNormalize{ _shouldNormalize }
		{
		}
	};
}

#endif // GUARD
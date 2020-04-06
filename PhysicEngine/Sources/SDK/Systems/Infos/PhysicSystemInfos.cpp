#include <SDK/Systems/Infos/PhysicSystemInfos.hpp>

namespace Pe
{
	float PhysicSystemInfos::fixedTime = 0.02f;
	ForceInfos PhysicSystemInfos::gravityInfos(Vec2(0.0f, -9.81f), ForceMode::Acceleration);

	std::vector<IBroadPhase*> PhysicSystemInfos::broadPhases;
	std::vector<INarrowPhase*> PhysicSystemInfos::narrowPhases;

	void PhysicSystemInfos::ResetGravity()
	{
		gravityInfos.force = Vec2(0.0f, -9.81f);
	}
}
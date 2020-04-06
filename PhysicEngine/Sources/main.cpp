#include <SDK/Engine.hpp>

#include <SDK/Scene/Examples/SceneDebugCollision.hpp>
#include <SDK/Scene/Examples/SceneBouncingPoly.hpp>
#include <SDK/Scene/Examples/SceneCircles.hpp>
#include <SDK/Scene/Examples/SceneTower.hpp>
#include <SDK/Scene/Examples/SceneBigShapeSimple.hpp>
#include <SDK/Scene/Examples/SceneBigShapeComplex.hpp>
using namespace Pe;

int main(int argc, char** argv)
{
	Engine en;

	// Render infos.
	RenderSystemInfos::appName = "Physic Engine";
	RenderSystemInfos::windowDimention = Vec2(1280, 960);


	// Physic infos.
	PhysicSystemInfos::fixedTime = 0.02f;
	PhysicSystemInfos::broadPhases = {
		new SweepAndPrune_BP(),
		new DynamicAABBTree_BP()
	};
	PhysicSystemInfos::narrowPhases = {
		new SAT_NP(),
		new GJK_NP()
	};


	// Scene infos.
	SceneSystemInfos::scenes = {
		new SceneDebugCollision(),
		new SceneBouncingPoly(200),
		new SceneBouncingPoly(500),
		new SceneCircles(),
		new SceneTower(),
		new SceneBigShapeSimple(),
		new SceneBigShapeComplex()
	};


	en.Launch();

	return 0;
}
#include <Maths/Shapes/Triangle.hpp>

#include <SDK/Scene/Components/ShapeComponent.hpp>
#include <SDK/Scene/Components/Physics/DynamicBodyColor.hpp>
#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>

#include <SDK/Scene/Examples/SceneDebugCollision.hpp>

namespace Pe
{
	SceneDebugCollision::SceneDebugCollision(float _worldHeight) : SceneBase(_worldHeight, false)
	{
	}

	void SceneDebugCollision::Create()
	{
		SceneBase::Create();

		// First triangle.
		GameObj* firstObj = CreateGameObj();
		firstObj->tr.pos = Vec2(-5.0f, -5.0f);

		firstObj->AddComponent<ShapeComponent>(new Triangle(20.0f, 14.0f));
		firstObj->AddComponent<RenderShape>();
		DynamicBodyColor* firstBody = firstObj->AddComponent<DynamicBodyColor>();
		firstBody->isKinematic = true;
		firstBody->useGravity = false;
		firstBody->collisionColor = Color{ 1.0f, 0.4f, 1.0f };
		firstBody->coloredTime = 0.05f;


		// Second triangle.
		GameObj* secondObj = CreateGameObj();
		secondObj->tr.pos = Vec2(5.0f, 5.0f);

		secondObj->AddComponent<ShapeComponent>(new Triangle(14.0f, 20.0f));
		secondObj->AddComponent<RenderShape>();
		DynamicBodyColor* secondBody = secondObj->AddComponent<DynamicBodyColor>();
		secondBody->isKinematic = true;
		secondBody->useGravity = false;
		secondBody->coloredTime = 0.05f;
	}
}
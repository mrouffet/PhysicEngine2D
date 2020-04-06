#include <Maths/Shapes/Square.hpp>
#include <Maths/Shapes/Circle.hpp>

#include <SDK/Scene/Examples/SceneTower.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>

namespace Pe
{
	SceneTower::SceneTower(const Vec2& _towerPolyNum, float _worldScale) :
		SceneBase(_worldScale),
		mTowerPolyNum{ _towerPolyNum }
	{
	}

	void SceneTower::Create()
	{
		SceneBase::Create();

		constexpr float squareSize = 2.0f;
		float width = GetWorldWidth();
		float height = GetWorldHeight();

		Vec2 start = Vec2(-mTowerPolyNum.x * squareSize - 10.0f, -0.5f * height + 2.5f);


		// Add Square tower.
		auto square = ShapeHandle::Create(new Square(squareSize));
		
		for (int i = 0; i < mTowerPolyNum.x; ++i)
		{
			for (int j = 0; j < mTowerPolyNum.y; ++j)
			{
				GameObj* gObj = CreateGameObj();

				gObj->AddComponent<ShapeComponent>(square);
				gObj->AddComponent<RenderShape>()->color = Color{0.3f, 0.7f, 0.7f};

				DynamicBody* body = gObj->AddComponent<DynamicBody>();

				gObj->tr.pos = start + Vec2(static_cast<float>(i), static_cast<float>(j)) * squareSize;
			}
		}

		// Add Circle.
		GameObj* gObj = CreateGameObj();

		gObj->AddComponent<ShapeComponent>(new Circle(5.0f));
		gObj->AddComponent<RenderShape>()->color = Color{1.0f, 1.0f, 0.3f};

		DynamicBody* body = gObj->AddComponent<DynamicBody>();
		
		body->mass = 10.0f;
		body->AddForce(ForceParams(Vec2(-75.0f, 0.0f), ForceMode::Velocity, MotionMode::Linear));

		gObj->tr.pos = Vec2(15.0f, -5.0f);
	}
}
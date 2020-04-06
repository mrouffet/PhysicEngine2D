#include <Maths/Shapes/Square.hpp>
#include <Maths/Shapes/Circle.hpp>
#include <Maths/Shapes/Triangle.hpp>
#include <Maths/Shapes/Rectangle.hpp>

#include <SDK/Scene/Examples/SceneBigShapeSimple.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>

namespace Pe
{
	SceneBigShapeSimple::SceneBigShapeSimple(float _worldScale) :
		SceneBase(_worldScale)
	{
	}

	void SceneBigShapeSimple::Create()
	{
		SceneBase::Create();

		float width = GetWorldWidth();
		float height = GetWorldHeight();

		// Static block.
		GameObj* blockObj = CreateGameObj(true);
		blockObj->tr.pos = Vec2(4.0f, -5.0f);

		blockObj->AddComponent<ShapeComponent>(new Square(10.0f));
		blockObj->AddComponent<RenderShape>()->color = Color{0.25f, 0.7f, 0.25f};

		blockObj->AddComponent<StaticBody>();

		// Rectangle
		GameObj* rectObj = CreateGameObj();
		rectObj->tr.pos = Vec2(10.0f, 5.0f);

		rectObj->AddComponent<ShapeComponent>(new Rectangle(35.0f, 7.0f));
		rectObj->AddComponent<RenderShape>();

		rectObj->AddComponent<DynamicBody>();

		// Squares.
		auto square = ShapeHandle::Create(new Square(6.0f));

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				GameObj* squareObj = CreateGameObj();
				squareObj->tr.pos = Vec2(15.0f + j * 7.0f, 12.0f + i * 7.0f);

				squareObj->AddComponent<ShapeComponent>(square);
				squareObj->AddComponent<RenderShape>()->color = Color{0.2f, 0.35f, 1.0f};

				squareObj->AddComponent<DynamicBody>();
			}
		}

		// Triangle
		GameObj* triObj = CreateGameObj();
		triObj->tr.pos = Vec2(0.0f, 9.0f);

		triObj->AddComponent<ShapeComponent>(new Triangle(4.0f, 5.0f));
		triObj->AddComponent<RenderShape>()->color = Color{ 0.7f, 0.2f, 0.7f };

		triObj->AddComponent<DynamicBody>();

		// Circle
		GameObj* circleObj = CreateGameObj();
		circleObj->tr.pos = Vec2(-20.0f, 5.0f);

		circleObj->AddComponent<ShapeComponent>(new Circle(8.0f));
		circleObj->AddComponent<RenderShape>()->color = Color{ 1.0f, 1.0f, 0.3f };

		circleObj->AddComponent<DynamicBody>();
	}
}
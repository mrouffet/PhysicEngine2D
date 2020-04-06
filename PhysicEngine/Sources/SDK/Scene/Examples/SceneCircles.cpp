#include <Maths/Shapes/Circle.hpp>
#include <Maths/Shapes/Square.hpp>

#include <SDK/Scene/Examples/SceneCircles.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>

#include <Core/Debug.hpp>

namespace Pe
{
	Color chainColors[] =
	{
		Color{1.0f, 0.2f, 0.2f},
		Color{0.2f, 1.0f, 0.2f},
		Color{0.2f, 0.2f, 1.0f},
		Color{1.0f, 1.0f, 0.2f},
		Color{1.0f, 0.2f, 1.0f},
		Color{0.2f, 1.0f, 1.0f},
	};

	constexpr unsigned int chainColorSize = sizeof(chainColors) / sizeof(Color);

	SceneCircles::SceneCircles(float _worldScale) : SceneBase(_worldScale)
	{
	}

	void SceneCircles::Create()
	{
		SceneBase::Create();

		float width = GetWorldWidth();
		float height = GetWorldHeight();

		auto circle = ShapeHandle::Create(new Circle(1.7f));

		// Horizontal chains
		for (unsigned int i = 0; i < 5; ++i)
		{
			for (unsigned int j = 0; j < 5; ++j)
			{
				GameObj* gObj = CreateGameObj();

				gObj->AddComponent<ShapeComponent>(circle);
				gObj->AddComponent<RenderShape>()->color = chainColors[j];

				DynamicBody* body = gObj->AddComponent<DynamicBody>();
				body->bounciness = 0.7f;

				gObj->tr.pos = Vec2(-20.0f + 5.0f * i, -22.0f + 10.0f * j);
				body->AddForce(ForceParams(Vec2(35.0f, 0.0f), ForceMode::Impulse, MotionMode::Linear));
			}
		}

		// Vertical chains
		for (unsigned int i = 0; i < 1; ++i)
		{
			for (unsigned int j = 0; j < 8; ++j)
			{
				GameObj* gObj = CreateGameObj();

				gObj->AddComponent<ShapeComponent>(circle);
				gObj->AddComponent<RenderShape>()->color = chainColors[chainColorSize - 1 - i];

				DynamicBody* body = gObj->AddComponent<DynamicBody>();

				gObj->tr.pos = Vec2(20.0f + -5.0f * i, 22.0f + -5.0f * j);
			}
		}


		// Static block.
		GameObj* blockObj = CreateGameObj(true);
		blockObj->tr.pos = Vec2(-18.0f, 12.5f);

		blockObj->AddComponent<ShapeComponent>(new Square(4.0f));
		blockObj->AddComponent<RenderShape>()->color = Color{ 0.25f, 0.7f, 0.25f };

		blockObj->AddComponent<StaticBody>();
	}
}
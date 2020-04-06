#include <Core/Random.hpp>

#include <Maths/Shapes/RandomShape.hpp>

#include <SDK/Scene/Examples/SceneBigShapeComplex.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>

namespace Pe
{
	Color randomColors[] =
	{
		Color{1.0f, 0.2f, 0.2f},
		Color{0.2f, 1.0f, 0.2f},
		Color{0.2f, 0.2f, 1.0f},

		Color{1.0f, 1.0f, 0.2f},
		Color{1.0f, 0.2f, 1.0f},
		Color{0.2f, 1.0f, 1.0f},

		Color{1.0f, 1.0f, 1.0f},
	};
	constexpr unsigned int randomColorSize = sizeof(randomColors) / sizeof(Color);


	SceneBigShapeComplex::SceneBigShapeComplex(unsigned int _polyCount, float _worldScale) :
		SceneBase(_worldScale),
		mPolyCount{ _polyCount }
	{
	}

	void SceneBigShapeComplex::Create()
	{
		SceneBase::Create();

		float width = GetWorldWidth();
		float height = GetWorldHeight();

		RandomShapeParams params;

		params.minRadius = 3.5f;
		params.maxRadius = 5.0f;
		params.minPoints = 3;
		params.maxPoints = 7;

		Vec2 minBounds = Vec2(-width * 0.5f + params.maxRadius * 3.0f, -height * 0.5f + params.maxRadius * 3.0f);
		Vec2 maxBounds = minBounds * -1.0f;

		for (unsigned int i = 0; i < mPolyCount; ++i)
		{
			GameObj* gObj = CreateGameObj();

			gObj->AddComponent<ShapeComponent>(new RandomShape(params));
			gObj->AddComponent<RenderShape>()->color = randomColors[Random::Value(0u, randomColorSize)];

			DynamicBody* body = gObj->AddComponent<DynamicBody>();
			body->bounciness = 0.2f;
		}
	}
}
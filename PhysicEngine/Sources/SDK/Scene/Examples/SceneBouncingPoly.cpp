#include <Core/Random.hpp>

#include <Maths/Shapes/RandomShape.hpp>

#include <SDK/Scene/Examples/SceneBouncingPoly.hpp>

#include <SDK/Systems/Infos/PhysicSystemInfos.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/DynamicBodyColor.hpp>

namespace Pe
{
	SceneBouncingPoly::SceneBouncingPoly(unsigned int _polyCount, float _worldScale) :
		SceneBase(_worldScale),
		mPolyCount{ _polyCount }
	{
	}

	void SceneBouncingPoly::Create()
	{
		SceneBase::Create();

		// Disable gravity at start.
		PhysicSystemInfos::gravityInfos.force = Vec2();

		float width = GetWorldWidth();
		float height = GetWorldHeight();

		RandomShapeParams params;

		params.minRadius = 1.0f;
		params.maxRadius = 1.0f;
		params.minPoints = 3;
		params.maxPoints = 7;

		Vec2 minBounds = Vec2(-width * 0.5f + params.maxRadius * 3.0f, -height * 0.5f + params.maxRadius * 3.0f);
		Vec2 maxBounds = minBounds * -1.0f;

		constexpr float minLinearSpeed = 1.0f;
		constexpr float maxLinearSpeed = 3.0f;

		constexpr float minAngularSpeed = 1.0f;
		constexpr float maxAngularSpeed = 3.0f;

		for (size_t i = 0; i < mPolyCount; ++i)
		{
			GameObj* gObj = CreateGameObj();

			gObj->AddComponent<ShapeComponent>(new RandomShape(params));
			gObj->AddComponent<RenderShape>();

			DynamicBody* body = gObj->AddComponent<DynamicBodyColor>();

			body->mass = Random::Value(1.0f, 5.0f);
			body->bounciness = 1.0f;

			gObj->tr.rot.SetAngle(Random::Value(-180.0f, 180.0f));
			gObj->tr.pos.x = Random::Value(minBounds.x, maxBounds.x);
			gObj->tr.pos.y = Random::Value(minBounds.y, maxBounds.y);

			Mat2 linearRot;
			linearRot.SetAngle(Random::Value(-180.0f, 180.0f));
			body->AddForce(ForceParams(linearRot.x * Random::Value(minLinearSpeed, maxLinearSpeed), ForceMode::Velocity, MotionMode::Linear));

			Mat2 angularRot;
			angularRot.SetAngle(Random::Value(-180.0f, 180.0f));
			body->AddForce(ForceParams(angularRot.x * Random::Value(minAngularSpeed, maxAngularSpeed), ForceMode::Velocity, MotionMode::Angular));
		}
	}
}
#include <SDk/Engine.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>

#include <SDK/Scene/Components/Behaviors/TriangleSpawner.hpp>

namespace Pe
{
	std::shared_ptr<ShapeHandle> TriangleSpawner::sTriangleShape = ShapeHandle::Create(new Triangle(7.0f, 4.0f));

	void TriangleSpawner::Update(float _frameTime) noexcept
	{
		if (Engine::GetInputSystem().IsKeyUp(Key::K_P))
		{
			mHasSpawn = false;
			return;
		}
		else if (mHasSpawn)
			return;

		mHasSpawn = true;

		GameObj* newObj = Engine::GetSceneSystem().GetActiveScene()->CreateGameObj();
		newObj->tr.pos = Engine::GetRenderSystem().GetWorldMousePosition();;

		newObj->AddComponent<ShapeComponent>(sTriangleShape);
		newObj->AddComponent<RenderShape>();
		newObj->AddComponent<StaticBody>();
	}
}
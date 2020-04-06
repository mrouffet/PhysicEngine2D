#include <SDK/Engine.hpp>

#include <Maths/Shapes/Rectangle.hpp>

#include <Renderer/Window.hpp>

#include <SDK/Scene/SceneBase.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>
#include <SDK/Scene/Components/Physics/StaticBody.hpp>

#include <SDK/Scene/Components/Behaviors/PolygonMover.hpp>
#include <SDK/Scene/Components/Behaviors/TriangleSpawner.hpp>
#include <SDK/Scene/Components/Behaviors/ScrollScale.hpp>

namespace Pe
{
	SceneBase::SceneBase(float _worldScale, bool _hasBorder) :
		worldScale{ _worldScale },
		hasBorder{ _hasBorder }
	{
	}

	float SceneBase::GetWorldWidth() const
	{
		return Engine::GetRenderSystem().GetWindow().GetRatio() * worldScale;
	}
	float SceneBase::GetWorldHeight() const
	{
		// Height based on world scale.
		return worldScale;
	}
	float SceneBase::GetWorldScale() const
	{
		return worldScale;
	}

	void SceneBase::Create()
	{
		if (hasBorder)
			CreateBorderRectangles();

		GameObj* toolObj = CreateGameObj();
		toolObj->AddComponent<DebugPersp>();
		toolObj->AddComponent<DebugText>(); // Warning: This moves the object.
		toolObj->AddComponent<PolygonMover>();
		toolObj->AddComponent<TriangleSpawner>();
		toolObj->AddComponent<ScrollScale>();

		// Reset gravity state.
		PhysicSystemInfos::ResetGravity();
	}

	void SceneBase::Destroy()
	{
		for (unsigned int i = 0; i < mGameObjs.size(); ++i)
			delete mGameObjs[i];

		mGameObjs.clear();
	}

	GameObj* SceneBase::CreateGameObj(bool _isStatic)
	{
		GameObj* obj = new GameObj(_isStatic);
		mGameObjs.push_back(obj);

		return obj;
	}

	void SceneBase::CreateBorderRectangles()
	{
		float halfWidth = GetWorldWidth() * 0.5f;
		float halfHeight = GetWorldHeight() * 0.5f;

		
		auto horizontalRect = ShapeHandle::Create(new Rectangle(halfWidth * 2.0f - 1.001f, 1.0f));
		auto verticalRect = ShapeHandle::Create(new Rectangle(1.0f, halfHeight * 2.0f - 1.001f));

		// Top border.
		GameObj* borderObj = CreateGameObj(true);
		borderObj->tr.pos = Vec2(0.5f, halfHeight - 0.5f);
		borderObj->AddComponent<ShapeComponent>(horizontalRect);
		borderObj->AddComponent<RenderShape>()->color = Color{ 0.5f, 0.5f, 0.8f };
		borderObj->AddComponent<StaticBody>()->bounciness = 1.0f;


		// Bottom border.
		borderObj = CreateGameObj(true);
		borderObj->tr.pos = Vec2(-0.5f, -halfHeight + 0.5f);
		borderObj->AddComponent<ShapeComponent>(horizontalRect);
		borderObj->AddComponent<RenderShape>()->color = Color{ 0.5f, 0.5f, 0.8f };
		borderObj->AddComponent<StaticBody>()->bounciness = 1.0f;


		// Left border.
		borderObj = CreateGameObj(true);
		borderObj->tr.pos = Vec2(-halfWidth + 0.5f, 0.5f);
		borderObj->AddComponent<ShapeComponent>(verticalRect);
		borderObj->AddComponent<RenderShape>()->color = Color{ 0.5f, 0.5f, 0.8f };
		borderObj->AddComponent<StaticBody>()->bounciness = 1.0f;


		// Right border.
		borderObj = CreateGameObj(true);
		borderObj->tr.pos = Vec2(halfWidth - 0.5f, -0.5f);
		borderObj->AddComponent<ShapeComponent>(verticalRect);
		borderObj->AddComponent<RenderShape>()->color = Color{ 0.5f, 0.5f, 0.8f };
		borderObj->AddComponent<StaticBody>()->bounciness = 1.0f;
	}
}
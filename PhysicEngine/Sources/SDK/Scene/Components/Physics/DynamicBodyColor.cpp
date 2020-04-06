#include <Core/Debug.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Render/RenderComponent.hpp>

#include <SDK/Scene/Components/Physics/DynamicBodyColor.hpp>

namespace Pe
{
	void DynamicBodyColor::Start() noexcept
	{
		DynamicBody::Start();

		mRender = gObj->GetComponent<RenderComponent>();

		ASSERT(mRender, "gObj doesn't own RenderComponent!");

		mBaseColor = mRender->color;
	}

	void DynamicBodyColor::Update(float _frameTime) noexcept
	{
		DynamicBody::Update(_frameTime);

		if (mCurrTime < 0.0f)
			return;

		mCurrTime += _frameTime;

		if (mCurrTime > coloredTime)
		{
			mCurrTime = -1.0f;
			mRender->color = mBaseColor;
		}
	}

	void DynamicBodyColor::OnCollision(const CollisionInfos& _infos) noexcept
	{
		DynamicBody::OnCollision(_infos);

		mCurrTime = 0.0f;
		mRender->color = collisionColor;
	}
}
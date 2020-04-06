#include <SDK/Engine.hpp>

#include <Maths/Mat2.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Behaviors/PolygonMover.hpp>
#include <SDK/Scene/Components/Physics/DynamicBody.hpp>

namespace Pe
{
	RenderShape* PolygonMover::GetClickedShape() const
	{
		Vec2 pt, n;

		const RenderSystem& rendSys = Engine::GetRenderSystem();

		Vec2 mousePoint = rendSys.GetWorldMousePosition();

		const std::vector<RenderPersp*>& renders = rendSys.GetPerspRenders();

		for (unsigned int i = 0; i < renders.size(); ++i)
		{
			if (renders[i]->gObj->isStatic)
				continue;

			RenderShape* render = dynamic_cast<RenderShape*>(renders[i]);

			if (render && render->GetShape()->IsPointInside(mousePoint))
				return render;
		}

		return nullptr;
	}

	void PolygonMover::Update(float _frameTime) noexcept
	{
		const InputSystem& inputs = Engine::GetInputSystem();
		const RenderSystem& rendSys = Engine::GetRenderSystem();

		bool askTranslate = inputs.GetMouseButton(0);
		bool askRotate = inputs.GetMouseButton(2);

		Vec2 mousePoint = rendSys.GetWorldMousePosition();

		if (askTranslate || askRotate)
		{
			if (!mSelected)
			{
				mSelected = GetClickedShape();

				mClickMousePos = mPrevMousePos = rendSys.GetWorldMousePosition();

				if (mSelected)
				{
					mMouseLinearVelocity = mMouseAngularVelocity = Vec2();
					
					mClickAngle = mSelected->gObj->tr.rot.GetAngle();

					// Reset and stop body velocity.
					if (DynamicBody* body = mSelected->gObj->GetComponent<DynamicBody>())
					{
						prevKinematic = body->isKinematic;
						body->isKinematic = true;
					}
				}
			}
			else
			{
				Vec2 mouseDelta = mousePoint - mPrevMousePos;

				if (askTranslate)
				{
					mSelected->gObj->tr.pos += mousePoint - mPrevMousePos;

					if (mouseDelta.GetSqrNorm() > 0.0f)
						mMouseLinearVelocity = mouseDelta * 100.0f;
				}
				else
				{
					Vec2 from = mClickMousePos - mSelected->gObj->tr.pos;
					Vec2 to = mousePoint - mSelected->gObj->tr.pos;

					mSelected->gObj->tr.rot.SetAngle(mClickAngle + from.GetAngle(to));

					if (mouseDelta.GetSqrNorm() > 0.0f)
						mMouseAngularVelocity = mouseDelta * 100.0f;
				}

				mPrevMousePos = mousePoint;
			}
		}
		else if(mSelected)
		{
			if (DynamicBody* body = mSelected->gObj->GetComponent<DynamicBody>())
			{
				body->isKinematic = prevKinematic;

				// Set mouse velocity
				body->linearVelocity = Vec2();
				body->angularVelocity = 0.0f;

				//body->linearVelocity = body->angularVelocity = Vec2();
				body->AddForce(ForceParams{ mMouseLinearVelocity, ForceMode::Velocity, MotionMode::Linear });
				body->AddForce(ForceParams{ mMouseAngularVelocity, ForceMode::Velocity, MotionMode::Angular });
			}

			mSelected = nullptr;
		}
	}
}
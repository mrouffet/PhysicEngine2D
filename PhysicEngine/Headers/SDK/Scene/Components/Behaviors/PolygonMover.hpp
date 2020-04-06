#pragma once

#ifndef PE_POLYGON_MOVER_GUARD
#define PE_POLYGON_MOVER_GUARD

#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>

namespace Pe
{
	class PolygonMover : public Component
	{
		bool prevKinematic = false;
		RenderShape* mSelected = nullptr;

		Vec2 mPrevMousePos;
		Vec2 mClickMousePos;
		float mClickAngle = 0.0f;

		Vec2 mMouseLinearVelocity;
		Vec2 mMouseAngularVelocity;

		RenderShape* GetClickedShape() const;

	public:
		using Component::Component;

		void Update(float _frameTime) noexcept override final;
	};
}

#endif // GUARD
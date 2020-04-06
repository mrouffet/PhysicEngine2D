#pragma once

#ifndef PE_DYNAMIC_BODY_COLOR_GUARD
#define PE_DYNAMIC_BODY_COLOR_GUARD

#include <Core/Color.hpp>

#include <SDK/Scene/Components/Physics/DynamicBody.hpp>

namespace Pe
{
	class RenderComponent;

	class DynamicBodyColor : public DynamicBody
	{
		RenderComponent* mRender = nullptr;

		Color mBaseColor;

		float mCurrTime = 0.0f;

	public:
		using DynamicBody::DynamicBody;

		float coloredTime = 0.15f;
		Color collisionColor = Color{1.0f, 1.0f, 0.2f};

		void Start() noexcept override;
		void Update(float _frameTime) noexcept override final;

		void OnCollision(const CollisionInfos& _infos) noexcept override final;
	};
}

#endif
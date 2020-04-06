#pragma once

#ifndef PE_AABB_COMPONENT_GUARD
#define PE_AABB_COMPONENT_GUARD

#include <Maths/AABB.hpp>

#include <SDK/Scene/Components/ShapeComponent.hpp>
#include <SDK/Scene/Components/Physics/PhysicComponent.hpp>

namespace Pe
{
	class AABBComponent : public PhysicComponent, public AABB
	{
		ShapeComponent* mShape = nullptr;

	public:
		using PhysicComponent::PhysicComponent;

		ShapeComponent* GetShape() const noexcept;

		void Start() noexcept;

		void FixedUpdate(float _fixedTime) noexcept override final;

		void Register() noexcept override final;

		void DrawDebug() noexcept override final;
	};
}

#endif // GUARD
#pragma once

#ifndef PE_BODY_BASE_GUARD
#define PE_BODY_BASE_GUARD

#include <Core/Pair.hpp>

#include <Maths/Shapes/Shape.hpp>

#include <SDK/Scene/Components/Physics/AABBComponent.hpp>
#include <SDK/Scene/Components/Physics/PhysicComponent.hpp>

namespace Pe
{
	class BodyBase : public PhysicComponent
	{
	public:
		float bounciness = 0.4f;
		float staticFriction = 0.1f;

		const AABBComponent* aabb = nullptr;

		BodyBase(GameObj* _obj) noexcept;

		ShapeComponent* GetShape() const noexcept;

		void Register() noexcept override final;

		virtual bool IsStatic() const = 0;
		virtual void OnCollision(const struct CollisionInfos& _infos) noexcept = 0;
	};

	using BodyPair = Pair<BodyBase*, BodyBase*>;
}

#endif // GUARD
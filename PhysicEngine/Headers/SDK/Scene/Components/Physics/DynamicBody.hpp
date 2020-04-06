#pragma once

#ifndef PE_DYNAMIC_BODY_GUARD
#define PE_DYNAMIC_BODY_GUARD

#include <list>

#include <Physics/Forces/ForceInfos.hpp>
#include <Physics/Forces/ForceConstraints.hpp>

#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	class DynamicBody : public BodyBase
	{
		float mShapeInertia = -1.0f;

		std::list<ForceInfos> mLinearForces;
		std::list<ForceInfos> mAngularForces;

		Vec2 ComputeLinearForce(const ForceInfos& fInfos, float _fixedTime);
		float ComputeAngularForce(const ForceInfos& fInfos, float _fixedTime);

		void ComputeLinearForces(float _fixedTime);
		void ComputeAngularForces(float _fixedTime);

		void ApplyLinearConstraints();

	public:
		using BodyBase::BodyBase;

		bool useGravity = true;
		bool useCollisionResponse = true;
		bool isKinematic = false;

		float mass = 1.0f;

		unsigned int linearConstraints = 0;

		float linearDrag = 0.0f;
		float angularDrag = 0.0f;

		Vec2 linearVelocity;
		float angularVelocity;

		float GetInertiaTensor() const;
		float GetInverseInertiaTensor() const;

		void AddForce(const ForceParams& _fParams) noexcept;

		void Start() noexcept override;
		void FixedUpdate(float _fixedTime) noexcept override final;

		bool IsStatic() const override;
		void OnCollision(const CollisionInfos& _infos) noexcept override;
	};
}

#endif // GUARD
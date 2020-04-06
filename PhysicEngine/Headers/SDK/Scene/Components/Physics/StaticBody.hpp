#pragma once

#ifndef PE_STATIC_BODY_GUARD
#define PE_STATIC_BODY_GUARD

#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	class StaticBody : public BodyBase
	{
	public:
		using BodyBase::BodyBase;

		void FixedUpdate(float _fixedTime) noexcept override final;

		bool IsStatic() const override;
		void OnCollision(const CollisionInfos& _infos) noexcept override final;
	};
}

#endif // GUARD
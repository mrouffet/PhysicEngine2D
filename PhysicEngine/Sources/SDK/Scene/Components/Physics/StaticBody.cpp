#include <SDK/Engine.hpp>

#include <SDK/Physics/CollisionInfos.hpp>

#include <SDK/Scene/Components/Physics/StaticBody.hpp>

namespace Pe
{
	void StaticBody::FixedUpdate(float _fixedTime) noexcept
	{
	}

	bool StaticBody::IsStatic() const
	{
		return true;
	}
	void StaticBody::OnCollision(const CollisionInfos& _infos) noexcept
	{
	}
}
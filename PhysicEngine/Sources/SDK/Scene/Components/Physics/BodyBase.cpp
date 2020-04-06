#include <SDK/Engine.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Physics/BodyBase.hpp>

namespace Pe
{
	BodyBase::BodyBase(GameObj* _obj) noexcept :
		PhysicComponent(_obj),
		aabb{ _obj->AddComponent<AABBComponent>() }
	{
	}

	ShapeComponent* BodyBase::GetShape() const noexcept
	{
		return aabb->GetShape();
	}

	void BodyBase::Register() noexcept
	{
		Engine::GetPhysicSystem().Register(this);
	}
}
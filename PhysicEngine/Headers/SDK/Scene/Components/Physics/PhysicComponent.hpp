#pragma once

#ifndef PE_PHYSIC_COMPONENT_GUARD
#define PE_PHYSIC_COMPONENT_GUARD

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	class PhysicComponent : public Component
	{
	public:
		using Component::Component;

		virtual void FixedUpdate(float _fixedTime) noexcept = 0;
	};
}

#endif // GUARD
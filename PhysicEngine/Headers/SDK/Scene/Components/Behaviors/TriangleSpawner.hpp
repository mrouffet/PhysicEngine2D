#pragma once

#ifndef PE_TRIANGLE_SPAWNER_GUARD
#define PE_TRIANGLE_SPAWNER_GUARD

#include <Maths/Shapes/Triangle.hpp>

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	class TriangleSpawner : public Component
	{
		bool mHasSpawn = false;

		static std::shared_ptr<ShapeHandle> sTriangleShape;

	public:
		using Component::Component;

		void Update(float _frameTime) noexcept override final;
	};
}

#endif // GUARD
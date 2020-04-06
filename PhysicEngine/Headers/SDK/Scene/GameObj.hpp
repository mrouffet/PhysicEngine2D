#pragma once

#ifndef PE_GAME_OBJ_GUARD
#define PE_GAME_OBJ_GUARD

#include <vector>

#include <Maths/Transform.hpp>

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	class GameObj
	{
		std::vector<Component*> mComponents;

	public:
		const bool isStatic;

		GameObj(bool _isStatic = false);
		~GameObj();

		Transform tr;

		template <typename T>
		T* GetComponent() const;

		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);
	};
}

#include <SDK/Scene/GameObj.inl>

#endif // GUARD
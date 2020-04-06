#pragma once

#ifndef PE_COMPONENT_GUARD
#define PE_COMPONENT_GUARD

namespace Pe
{
	class GameObj;

	class Component
	{
	public:
		GameObj* const gObj = nullptr;
		bool isEnable = true;

		Component(GameObj* _obj) noexcept;
		Component(Component&& _other) noexcept;
		Component(const Component&) = delete;
		virtual ~Component() = default;

		virtual void Start() noexcept;
		virtual void Update(float _frameTime) noexcept;
		virtual void End() noexcept;

		virtual void Register() noexcept;

		virtual void DrawDebug() noexcept;
	};
}

#endif // GUARD
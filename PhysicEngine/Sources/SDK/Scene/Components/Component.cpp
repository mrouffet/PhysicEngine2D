#include <SDK/Engine.hpp>

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	Component::Component(GameObj* _obj) noexcept : gObj{ _obj }
	{
	}
	Component::Component(Component&& _other) noexcept : gObj{ _other.gObj }
	{
	}

	void Component::Start() noexcept
	{
	}
	void Component::Update(float _frameTime) noexcept
	{
	}
	void Component::End() noexcept
	{
	}

	void Component::Register() noexcept
	{
		Engine::GetSceneSystem().Register(this);
	}

	void Component::DrawDebug() noexcept
	{
	}
}
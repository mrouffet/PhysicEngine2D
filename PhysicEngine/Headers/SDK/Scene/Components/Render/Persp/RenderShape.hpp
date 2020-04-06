#pragma once

#ifndef PE_RENDER_SHAPE_GUARD
#define PE_RENDER_SHAPE_GUARD

#include <SDK/Scene/Components/ShapeComponent.hpp>
#include <SDK/Scene/Components/Render/Persp/RenderPersp.hpp>

namespace Pe
{
	class RenderShape : public RenderPersp
	{
		ShapeComponent* mShape = nullptr;

		void CreateBuffers() noexcept;
		void DestroyBuffers() noexcept;
		void BindBuffers() noexcept;

	public:
		using RenderPersp::RenderPersp;

		ShapeComponent* GetShape() const noexcept;

		void Start() noexcept override final;
		void End() noexcept override final;

		void Draw() noexcept override final;
	};
}

#endif // GUARD
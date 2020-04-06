#pragma once

#ifndef PE_DEBUG_PERSP_GUARD
#define PE_DEBUG_PERSP_GUARD

#include <vector>

#include <Core/Color.hpp>
#include <Maths/Vec2.hpp>
#include <Maths/AABB.hpp>

#include <SDK/Miscs/DrawDebugState.hpp>

#include <SDK/Scene/Components/Render/Persp/RenderPersp.hpp>

namespace Pe
{
	namespace Debug
	{
		extern DrawDebugState sDrawDebugFlags;

		void DrawLine(const Vec2& _start, const Vec2& _end, const Color& _color = Color{1.0f, 1.0f, 1.0f});

		void DrawRectangle(const AABB& _geometry, const Color& _color = Color());
		void DrawRectangle(const Vec2& _min, const Vec2& _max, float _angle = 0.0f, const Color& _color = Color{ 1.0f, 1.0f, 1.0f });
		void DrawRectangle(float _width, float _height, const Vec2& _pos, float _angle = 0.0f, const Color& _color = Color{ 1.0f, 1.0f, 1.0f });
	}


	class DebugPersp : public RenderPersp
	{
		static unsigned int sVertexBufferID;

	public:
		using RenderPersp::RenderPersp;

		void Start() noexcept override final;
		void End() noexcept override final;

		void Draw() noexcept override final;

		void BindBuffers() noexcept;
	};
}

#endif // GUARD
#include <GL/glew.h>

#include <Maths/Algorithms.hpp>
#include <Maths/Mat2.hpp>

#include <Core/Debug.hpp>

#include <SDK/Scene/Components/Render/Persp/DebugPersp.hpp>

namespace Pe
{
	namespace Debug
	{
#if PE_DEBUG
		DrawDebugState sDrawDebugFlags = DrawDebugState::RecapLandmarks;
#else
		DrawDebugState sDrawDebugFlags = DrawDebugState::None;
#endif

		struct DrawDebugRectInfos
		{
			float width = 0.0f;
			float height = 0.0f;

			Vec2 position;
			float angle = 0.0f;

			Color color;
		};

		std::vector<DrawDebugRectInfos> sDebugRectInfos;

		void DrawLine(const Vec2& _start, const Vec2& _end, const Color& _color)
		{
			Vec2 dir = _end - _start;
			float angle = Vec2(1.0f, 0.0f).GetAngle(dir);

			sDebugRectInfos.push_back({ dir.GetNorm(), 0.0001f, _start + dir * 0.5f, angle, _color });
		}

		void DrawRectangle(const AABB& _geometry, const Color& _color)
		{
			DrawRectangle(_geometry.min, _geometry.max, 0.0f, _color);
		}
		void DrawRectangle(const Vec2& _min, const Vec2& _max, float _angle, const Color& _color)
		{
			Vec2 center = _min + (_max - _min) / 2.0f;

			DrawRectangle(_max.x - _min.x, _max.y - _min.y, center, _angle, _color);
		}
		void DrawRectangle(float _width, float _height, const Vec2& _pos, float _angle, const Color& _color)
		{
			sDebugRectInfos.push_back({ _width, _height, _pos, _angle, _color });
		}
	}

	unsigned int DebugPersp::sVertexBufferID = 0;

	void DebugPersp::Start() noexcept
	{
		if (sVertexBufferID != 0)
			return;
		
		float vertices[12]{
			-0.5f, -0.5f, 0.0f,				// Point A
			0.5f, -0.5f, 0.0f,				// Point B
			0.5f, 0.5f, 0.0f,				// Point C
			-0.5f, 0.5f, 0.0f,				// Point D
		};

		glGenBuffers(1, &sVertexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, sVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void DebugPersp::End() noexcept
	{
		if (sVertexBufferID == 0)
			return;

		glDeleteBuffers(1, &sVertexBufferID);
		sVertexBufferID = 0;
	}

	void DebugPersp::Draw() noexcept
	{
		for (auto it = Debug::sDebugRectInfos.begin(); it != Debug::sDebugRectInfos.end(); ++it)
		{
			glColor3f(it->color.r, it->color.g, it->color.b);

			float cos = cosf(it->angle * Algo::DegToRad);
			float sin = sinf(it->angle * Algo::DegToRad);

			float transfMat[16] =
			{
				cos * it->width, sin * it->width, 0.0f, 0.0f,
				-sin * it->height, cos * it->height, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
				it->position.x, it->position.y, -1.0f, 1.0f
			};

			glPushMatrix();
			glMultMatrixf(transfMat);

			BindBuffers();
			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glDisableClientState(GL_VERTEX_ARRAY);

			glPopMatrix();
		}

		Debug::sDebugRectInfos.clear();
	}

	void DebugPersp::BindBuffers() noexcept
	{
		if (sVertexBufferID == 0)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, sVertexBufferID);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, (void*)0);
	}
}
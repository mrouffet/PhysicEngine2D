#include <GL/glew.h>

#include <Maths/Algorithms.hpp>

#include <SDK/Engine.hpp>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Render/Persp/RenderShape.hpp>

namespace Pe
{
	ShapeComponent* RenderShape::GetShape() const noexcept
	{
		return mShape;
	}

	void RenderShape::Start() noexcept
	{
		mShape = gObj->GetComponent<ShapeComponent>();

		ASSERT(mShape, "RenderShape::Start(): ShapeComponent nullptr!");

		CreateBuffers();
	}
	void RenderShape::End() noexcept
	{
		DestroyBuffers();
	}

	void RenderShape::CreateBuffers() noexcept
	{
		if (mShape->GetHandle()->vertexBufferID != 0u)
			return;

		const Shape* rawShape = mShape->GetHandle()->shape;

		float* vertices = new float[3 * rawShape->pointNum];

		for (unsigned int i = 0; i < rawShape->pointNum; ++i)
		{
			vertices[3 * i] = rawShape->GetPoint(i).x;
			vertices[3 * i + 1] = rawShape->GetPoint(i).y;
			vertices[3 * i + 2] = 0.0f;
		}

		glGenBuffers(1, &mShape->GetHandle()->vertexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, mShape->GetHandle()->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * rawShape->pointNum, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		delete[] vertices;
	}
	void RenderShape::DestroyBuffers() noexcept
	{
		if (!mShape->GetHandle().unique() || mShape->GetHandle()->vertexBufferID == 0)
			return;

		glDeleteBuffers(1, &mShape->GetHandle()->vertexBufferID);
		mShape->GetHandle()->vertexBufferID = 0;
	}
	void RenderShape::BindBuffers() noexcept
	{
		if (mShape->GetHandle()->vertexBufferID == 0)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, mShape->GetHandle()->vertexBufferID);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, (void*)0);
	}

	void RenderShape::Draw() noexcept
	{
		// Set transforms (assuming model view mode is set)

		glPushMatrix();
		glMultMatrixf(gObj->tr.GetMatrix().data());

		// Draw vertices
		BindBuffers();
		glDrawArrays(GL_LINE_LOOP, 0, mShape->GetPoints().size());
		glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();
	}
}
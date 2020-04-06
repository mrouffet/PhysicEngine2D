#include <GL/glew.h>

#include <drawtext.h>

#include <SDK/Scene/GameObj.hpp>
#include <SDK/Scene/Components/Render/Ortho/RenderText.hpp>

namespace Pe
{
	void RenderText::Draw() noexcept
	{
		glTranslatef(gObj->tr.pos.x, gObj->tr.pos.y, 0.0f);
		glScalef(gObj->tr.scale.x, gObj->tr.scale.y, 0.0f);

		dtx_string(text.c_str());
	}
}
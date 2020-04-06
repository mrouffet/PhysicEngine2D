#include <Maths/Algorithms.hpp>

#include <SDK/Engine.hpp>
#include <SDK/Scene/GameObj.hpp>

#include <SDK/Scene/Components/Render/Ortho/DebugText.hpp>

namespace Pe
{
	namespace Debug
	{
		std::string sDebugText;

		struct DrawDebugTextInfos
		{
			std::string text;
			
			Vec2 position;
			Vec2 scale;
			
			Color color;
		};

		std::vector<DrawDebugTextInfos> sDebugTextInfos;

		void DrawText(const std::string& _str)
		{
			sDebugText += _str + '\n';
		}

		void DrawText(const std::string& _str, const Vec2& _pos, const Vec2& _scale, const Color& _color)
		{
			sDebugTextInfos.push_back(DrawDebugTextInfos{ _str, _pos, _scale, _color });
		}
	}

	void DebugText::Update(float _frameTime) noexcept
	{
		gObj->tr.pos = Vec2(50.0f, Engine::GetRenderSystem().GetWindow().GetHeight() - 40.0f);

		mLowFrameTime = Algo::Min(mLowFrameTime, _frameTime);
		mHighFrameTime = Algo::Max(mHighFrameTime, _frameTime);

		++mCountFrameTime;
		mCurrFPSTime += _frameTime;

		if (mCurrFPSTime < 0.5f)
			return;

		float accFrameTime = mCurrFPSTime;
		mCurrFPSTime = Algo::FMod(mCurrFPSTime, 0.5f);

		accFrameTime -= mCurrFPSTime;
		accFrameTime /= mCountFrameTime;

		mFPSText = "FPS:        Av: " + std::to_string(1.0f / accFrameTime) + "        low: " + std::to_string(1.0f / mHighFrameTime) + "        high: " + std::to_string(1.0f / mLowFrameTime) + '\n';

		mCountFrameTime = 0;
		mLowFrameTime = FLT_MAX;
		mHighFrameTime = -FLT_MAX;
	}

	void DebugText::Draw() noexcept
	{
		if (Debug::sDrawDebugFlags < DrawDebugState::RecapLandmarks)
			return;
	
		text = "F1: Debug " + std::to_string(static_cast<unsigned int>(Debug::sDrawDebugFlags)) + "        F2:  FPS Limit ";
		text += Engine::GetInstance().GetFPS() == FPS::Unlocked ? "Unlocked" : Engine::GetInstance().GetFPS() == FPS::Locked30 ? "30" : "60";
		text += '\n' + mFPSText + Debug::sDebugText;
		
		Debug::sDebugText = "";

		// Draw recap text.
		RenderText::Draw();


		// Draw position texts.
		Vec2 winDims = Engine::GetRenderSystem().GetWindow().GetDims();
		float ratio = Engine::GetRenderSystem().worldScale / winDims.y;
		winDims /= 2.0f;

		glPopMatrix();

		for (auto it = Debug::sDebugTextInfos.begin(); it != Debug::sDebugTextInfos.end(); ++it)
		{
			text = it->text;
			glColor3f(it->color.r, it->color.g, it->color.b);

			gObj->tr.pos = winDims + it->position / ratio;
			gObj->tr.scale = it->scale;
			
			glPushMatrix();

			RenderText::Draw();

			glPopMatrix();
		}

		Debug::sDebugTextInfos.clear();
	}

	void DebugText::Register() noexcept
	{
		Engine::GetRenderSystem().Register(this);
		Engine::GetSceneSystem().Register(this);
	}
}
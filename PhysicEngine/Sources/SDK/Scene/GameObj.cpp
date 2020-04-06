#include <SDK/Scene/GameObj.hpp>

namespace Pe
{
	GameObj::GameObj(bool _isStatic) : isStatic{ _isStatic }
	{
	}
	GameObj::~GameObj()
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
			delete *it;

		mComponents.clear();
	}
}
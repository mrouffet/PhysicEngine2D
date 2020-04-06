#include <Core/Random.hpp>

#include <ctime>

namespace Pe
{
	Random Random::RandomInitRAII;

	Random::Random() noexcept
	{
		srand(static_cast<unsigned int>(time(NULL)));
	}
}
namespace Pe
{
	template <typename T>
	T Random::Value(T _min, T _max) noexcept
	{
		return _min + (_max - _min) * static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
	}
}
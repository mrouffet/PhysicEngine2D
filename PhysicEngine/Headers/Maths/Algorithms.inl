namespace Pe
{
	namespace Algo
	{
		template <typename T>
		T Min(T _a, T _b) noexcept
		{
			return _a <= _b ? _a : _b;
		}

		template <typename T>
		T Max(T _a, T _b) noexcept
		{
			return _a > _b ? _a : _b;
		}

		template<typename T>
		T Clamp(T _val, T _min, T _max) noexcept
		{
			return Min(Max(_val, _min), _max);
		}
	}
}
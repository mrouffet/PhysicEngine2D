namespace Pe
{
	template <typename T1, typename T2>
	Pair<T1, T2>::Pair(T1 _first, T2 _second) noexcept :
		first{ _first },
		second{ _second }
	{
	}

	template <typename T1, typename T2>
	Pair<T1, T2> Pair<T1, T2>::GetReversed() const noexcept
	{
		return Pair(second, first);
	}

	template <typename T1, typename T2>
	static Pair<T1, T2> Pair<T1, T2>::Reverse(const Pair<T1, T2>& _pair) noexcept
	{
		return _pair.GetReversed();
	}
}
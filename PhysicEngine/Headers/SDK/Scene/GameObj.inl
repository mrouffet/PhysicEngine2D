namespace Pe
{
	template <typename T>
	T* GameObj::GetComponent() const
	{
		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			T* comp = dynamic_cast<T*>(*it);

			if (comp)
				return comp;
		}

		return nullptr;
	}

	template <typename T, typename... Args>
	T* GameObj::AddComponent(Args&&... args)
	{
		T* comp = new T(this, std::forward<Args>(args)...);
		comp->Register();

		mComponents.push_back(comp);
		return comp;
	}
}
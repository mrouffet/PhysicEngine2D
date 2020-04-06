namespace Pe
{
	template <typename T>
	void Hull::Graham(std::vector<T>& _cloudPoint) noexcept
	{
		// Graham Scan: https://en.wikipedia.org/wiki/Graham_scan

		// find lowest X point.
		T lowPoint = _cloudPoint.front();
		for (auto it = _cloudPoint.begin(); it != _cloudPoint.end(); ++it)
		{
			if (it->x < lowPoint.x)
				lowPoint = *it;
			else if (Algo::NearlyEqual(it->x, lowPoint.x) && it->y < lowPoint.y)
				lowPoint = *it;
		}

		// Sort by Slope.
		struct SlopeComparer
		{
			const T& point;

			SlopeComparer(const T& _point) : point{ _point }
			{
			}

			bool operator()(const T& _lhs, const T& _rhs) noexcept
			{
				if (_rhs == point)
					return false;
				if (_lhs == point)
					return true;

				return (_lhs - point).GetSlope() < (_rhs - point).GetSlope();
			}
		};

		std::sort(_cloudPoint.begin(), _cloudPoint.end(), SlopeComparer(lowPoint));

		// begin() + 2: Start with 2 points.
		for (auto it = _cloudPoint.begin() + 2; it != _cloudPoint.end(); ++it)
		{
			auto rIt = it - 1;

			while (rIt != _cloudPoint.begin())
			{
				auto prevRIt = rIt - 1;

				// Simplified double cross: (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
				float sign = (rIt->x - prevRIt->x) * (it->y - prevRIt->y) - (rIt->y - prevRIt->y) * (it->x - prevRIt->x);

				// Clock-wises sign: stop erasing.
				if (sign > 0.0f)
					break;

				rIt--;
			}

			// Erase all non clock-wise segments.
			if (rIt != it - 1)
				it = _cloudPoint.erase(rIt + 1, it) - 1;
		}
	}

	template <typename T>
	void Hull::Create(std::vector<T>& _cloudPoint) noexcept
	{
		// Can't create hull from triangle.
		if (_cloudPoint.size() <= 3u)
			return;

		struct TXComparer
		{
			bool operator()(const T& _lhs, const T& _rhs) noexcept
			{
				return _lhs.x < _rhs.x;
			}
		};

		// Trick to fast construct hull from 4 points.
		if (_cloudPoint.size() == 4u)
		{
			std::sort(_cloudPoint.begin(), _cloudPoint.end(), TXComparer());

			if (_cloudPoint[0].y < _cloudPoint[1u].y)
			{
				if ((_cloudPoint[1u] - _cloudPoint[2u]).GetSlope() < (_cloudPoint[1u] - _cloudPoint[3u]).GetSlope())
					std::swap(_cloudPoint[2u], _cloudPoint[3u]);
			}
			else if ((_cloudPoint[1u] - _cloudPoint[2u]).GetSlope() > (_cloudPoint[1u] - _cloudPoint[3u]).GetSlope())
				std::swap(_cloudPoint[2u], _cloudPoint[3u]);

			return;
		}

		// Use Graham for complex hull generation.
		Graham(_cloudPoint);
	}
}
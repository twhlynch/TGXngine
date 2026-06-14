#pragma once

#include <cmath>
#include <tuple>

namespace TGX
{
struct Point
{
	int x = 0;
	int y = 0;

	Point() = default;

	Point(int x, int y) : x(x), y(y) {}

	Point(float x, float y) : x(static_cast<int>(std::round(x))), y(static_cast<int>(std::round(y)))
	{
	}

	constexpr bool operator<(const Point &other) const noexcept
	{
		return std::tie(y, x) < std::tie(other.y, other.x);
	}

	constexpr bool operator==(const Point &other) const noexcept
	{
		return std::tie(y, x) == std::tie(other.y, other.x);
	}
};

struct PointUID
{
	int uid = 0;
	int x = 0;
	int y = 0;

	PointUID() = default;

	PointUID(int uid, int x, int y) : uid(uid), x(x), y(y) {}

	PointUID(int uid, float x, float y) : uid(uid), x(static_cast<int>(x)), y(static_cast<int>(y))
	{
	}

	constexpr bool operator<(const PointUID &other) const noexcept
	{
		return std::tie(y, x) < std::tie(other.y, other.x);
	}

	constexpr bool operator==(const PointUID &other) const noexcept
	{
		return uid == other.uid;
	}
};
} // namespace TGX

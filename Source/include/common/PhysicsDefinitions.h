#pragma once

#include <climits>

namespace TGX
{
struct FloatingPoint
{
	float x;
	float y;

	FloatingPoint() : x(0.0), y(0.0)
	{
	}

	FloatingPoint(float x, float y) : x(x), y(y)
	{
	}
};

struct FloatingPointUID
{
	int uid;
	float x;
	float y;

	FloatingPointUID() : uid(INT_MIN), x(0.0), y(0.0)
	{
	}

	FloatingPointUID(int uid, float x, float y) : uid(uid), x(x), y(y)
	{
	}

	~FloatingPointUID() = default;
};

struct Boundary
{
	float x;
	float y;
	float w;
	float h;

	Boundary() : x(0.0), y(0.0), w(0.0), h(0.0)
	{
	}

	Boundary(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
	{
	}

	~Boundary() = default;

	bool Contains(float newX, float newY) const
	{
		return (x <= newX + w &&
				x >= newX - w &&
				y <= newY + h &&
				y >= newY - h);
	}

	bool Intersect(const Boundary &range) const
	{
		return range.x - range.w <= this->x + this->w &&
			   range.x + range.w >= this->x - this->w &&
			   range.y - range.h <= this->y + this->h &&
			   range.y + range.h >= this->y - this->h;
	}

	bool Within(float _x, float _y) const
	{
		return _x >= x && _x <= w && _y >= y && _y <= h;
	}
};
} // namespace TGX

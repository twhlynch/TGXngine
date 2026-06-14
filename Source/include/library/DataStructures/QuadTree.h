#pragma once

#include "Core.h"
#include "PhysicsDefinitions.h"
#include "Point.h"

namespace TGX
{
class QuadTree
{
private:
	QuadTree *upperRight = nullptr;
	QuadTree *upperLeft = nullptr;
	QuadTree *lowerRight = nullptr;
	QuadTree *lowerLeft = nullptr;

	Boundary boundary;
	int capacity;
	Vector<PointUID> points;
	bool divided;
	int currentItemCount;
	inline static int size;

public:
	QuadTree(const Boundary &boundary, int n = 4)
		: boundary(boundary), capacity(n), divided(false), currentItemCount(0) {}

	~QuadTree()
	{
		delete upperRight;
		delete upperLeft;
		delete lowerRight;
		delete lowerLeft;
	}

	void Insert(int uid, float x, float y)
	{
		if (!boundary.Contains(x, y))
		{
			return;
		}

		if (currentItemCount < capacity)
		{
			points.emplace_back(uid, x, y);
			currentItemCount++;
			size++;
		}
		else
		{
			if (!divided)
			{
				SubDivide();
			}

			upperRight->Insert(uid, x, y);
			upperLeft->Insert(uid, x, y);
			lowerRight->Insert(uid, x, y);
			lowerLeft->Insert(uid, x, y);
		}
	}

	void SubDivide()
	{
		float x = boundary.x;
		float y = boundary.y;
		float w = boundary.w;
		float h = boundary.h;

		Boundary ur(x + (w / 2), y - (h / 2), w / 2, h / 2);
		Boundary ul(x - (w / 2), y - (h / 2), w / 2, h / 2);
		Boundary lr(x + (w / 2), y + (h / 2), w / 2, h / 2);
		Boundary ll(x - (w / 2), y + (h / 2), w / 2, h / 2);

		upperRight = new QuadTree(ur, capacity);
		upperLeft = new QuadTree(ul, capacity);
		lowerRight = new QuadTree(lr, capacity);
		lowerLeft = new QuadTree(ll, capacity);

		divided = true;
	}

	void Query(const Boundary &range, Set<PointUID> &found)
	{
		for (const auto &point : points)
		{
			if (range.Within(static_cast<float>(point.x), static_cast<float>(point.y)))
			{
				found.insert(point);
			}
		}

		if (divided)
		{
			upperRight->Query(range, found);
			upperLeft->Query(range, found);
			lowerRight->Query(range, found);
			lowerLeft->Query(range, found);
		}
	}

	static int Size()
	{
		return size;
	}

	void Clear()
	{
		size = 0;
		divided = false;
		currentItemCount = 0;
		points.clear();

		delete upperRight;
		upperRight = nullptr;
		delete upperLeft;
		upperLeft = nullptr;
		delete lowerRight;
		lowerRight = nullptr;
		delete lowerLeft;
		lowerLeft = nullptr;
	}
};
} // namespace TGX

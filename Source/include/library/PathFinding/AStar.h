#pragma once

#include <ankerl/unordered_dense.h>
#include <Common.hpp>
#include "ConfigurePath.h"
#include "Core.h"
#include "IPathfinding.h"
#include "Point.h"

namespace TGX
{
class AStar : public IPathfinding
{
public:
	void Test();
	void Search(
		const Point &start,
		const Point &end,
		int cols, int rows,
		const Vector<Vector<int>> &grid,
		const Unique<ConfigurePath> &configure) override;
	Vector<Point> GetPath() const override;

private:
	Vector<Point> path;
	int aStar_counter = 0;
	const int aStar_limit = 100;
	const int neighbour_limit = 8;
};
} // namespace TGX

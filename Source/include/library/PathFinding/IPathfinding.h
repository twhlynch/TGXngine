#pragma once

#include "ConfigurePath.h"
#include "Core.h"
#include "Point.h"

namespace TGX
{
enum class PathfindingAlgorithm : std::uint8_t
{
	AStar,
	Naval,
	Wave
};

class IPathfinding
{
public:
	virtual ~IPathfinding() = default;

	virtual void Search(
		const Point &start,
		const Point &end,
		int cols, int rows,
		const Vector<Vector<int>> &grid,
		const Unique<ConfigurePath> &configure) = 0;

	virtual Vector<Point> GetPath() const = 0;

	Unique<ConfigurePath> configurePath;
};
} // namespace TGX

#pragma once

#include <Common.hpp>
#include "ConfigurePath.h"
#include "Core.h"
#include "IPathfinding.h"
#include "Point.h"

namespace WoS
{
class WavePropagation : public IPathfinding
{
public:
	void Search(
		const Point &start,
		const Point &end,
		int cols, int rows,
		const Vector<Vector<int>> &grid,
		const Unique<ConfigurePath> &configurePath) override;

	Vector<Point> GetPath() const override;

	Vector<Vector<int>> GetField() const;

private:
	Vector<Vector<int>> flowField;
	Vector<Point> path;
};
} // namespace WoS

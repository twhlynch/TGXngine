#pragma once

#include <algorithm>
#include <cmath>
#include "CollisionStructures.h"
#include "Core.h"
#include "Flags.h"
#include "Globals.h"

namespace TGX
{
class Cells
{
public:
	inline static Map<int, CollisionCoords> tactical_uids_grid;

	inline static Map<String, int> tactical_grid;

	static void Init()
	{
		tactical_uids_grid.clear();
		tactical_grid.clear();
	}

	static void Add(
		int uid, float item_x, float item_y, float radius,
		int mapGridWidth, int mapGridHeight,
		Vector<Vector<int>> &passableGrid,
		Map<int, std::tuple<int, int, int, int>> &uids_grid,
		Map<String, int> &cells_grid,
		int cellMode = 0)
	{
		if (uids_grid.contains(uid))
		{
			return;
		}

		int x1 = std::max(static_cast<int>(std::floor(item_x - radius)), 0);
		int x2 = std::min(static_cast<int>(std::floor(item_x + radius)), mapGridWidth - 1);
		int y1 = std::max(static_cast<int>(std::floor(item_y - radius)), 0);
		int y2 = std::min(static_cast<int>(std::floor(item_y + radius)), mapGridHeight - 1);

		for (int x = x1; x <= x2; ++x)
		{
			for (int y = y1; y <= y2; ++y)
			{
				if (passableGrid[y][x] < Flags::CELL_COLLISION_MODE_HARD)
				{
					std::string cellKey = std::to_string(x) + " " + std::to_string(y);

					if (cells_grid.contains(cellKey))
					{
						int cellStack = cells_grid[cellKey];
						cellStack += cellMode;
						cells_grid[cellKey] = cellStack;
					}
					else
					{
						cells_grid[cellKey] = cellMode;
					}

					int cellStack = cells_grid[cellKey];
					if (cellStack >= Flags::CELL_COLLISION_MODE_MEDIUM && cellStack < Flags::CELL_COLLISION_MODE_HARD)
					{
						passableGrid[y][x] = Flags::CELL_COLLISION_MODE_MEDIUM;
					}
					else if (cellStack > Flags::CELL_COLLISION_MODE_OFF)
					{
						passableGrid[y][x] = Flags::CELL_COLLISION_MODE_SOFT;
					}
				}
			}
		}

		uids_grid[uid] = {x1, y1, x2, y2};
	}

	static void Remove(
		int uid, Vector<Vector<int>> &passableGrid,
		Map<int, std::tuple<int, int, int, int>> &uids_grid,
		Map<String, int> &cells_grid, int cellMode = 0)
	{
		auto it = uids_grid.find(uid);
		if (it == uids_grid.end())
		{
			return;
		}

		int x1 = std::get<0>(it->second);
		int y1 = std::get<1>(it->second);
		int x2 = std::get<2>(it->second);
		int y2 = std::get<3>(it->second);

		for (int x = x1; x <= x2; ++x)
		{
			for (int y = y1; y <= y2; ++y)
			{
				if (passableGrid[y][x] >= Flags::CELL_COLLISION_MODE_SOFT)
				{
					String cellKey = std::to_string(x) + " " + std::to_string(y);

					auto cellIt = cells_grid.find(cellKey);

					if (cellIt != cells_grid.end())
					{
						int cellStack = cellIt->second;
						cellStack -= cellMode;

						cells_grid[cellKey] = cellStack;

						if (cellStack == Flags::CELL_COLLISION_MODE_OFF)
						{
							passableGrid[y][x] = Flags::CELL_COLLISION_MODE_OFF;
						}
						else if (cellStack < Flags::CELL_COLLISION_MODE_MEDIUM)
						{
							passableGrid[y][x] = Flags::CELL_COLLISION_MODE_SOFT;
						}
					}
				}
			}
		}

		uids_grid.erase(uid);
	}

	Vector<int> TakeSnapshot(float item_x, float item_y, const CollisionGrid &collisionGrid, Vector<Vector<int>> &grid)
	{
		int x1, x2, y1, y2;

		x1 = x2 = y1 = y2 = 0;

		if (collisionGrid.radius > 0)
		{
			x1 = std::max(static_cast<int>(std::floor(item_x - collisionGrid.radius)), 0);
			x2 = std::min(static_cast<int>(std::floor(item_x + collisionGrid.radius)), Globals::mapGridWidth - 1);

			y1 = std::max(static_cast<int>(std::floor(item_y - collisionGrid.radius)), 0);
			y2 = std::min(static_cast<int>(std::floor(item_y + collisionGrid.radius)), Globals::mapGridHeight - 1);
		}
		else
		{
			x1 = std::max(static_cast<int>(std::floor(item_x - static_cast<float>(collisionGrid.gridX))), 0);
			x2 = std::min(static_cast<int>(std::floor(item_x + static_cast<float>(collisionGrid.gridX))), Globals::mapGridWidth - 1);

			y1 = std::max(static_cast<int>(std::floor(item_y - static_cast<float>(collisionGrid.gridY))), 0);
			y2 = std::min(static_cast<int>(std::floor(item_y + static_cast<float>(collisionGrid.gridY))), Globals::mapGridHeight - 1);
		}

		Vector<int> current_tiles;

		for (int x = x1; x <= x2; ++x)
		{
			for (int y = y1; y <= y2; ++y)
			{
				current_tiles.push_back(grid[y][x]);

				grid[y][x] = Flags::CELL_COLLISION_MODE_OFF;
			}
		}

		return current_tiles;
	}

	void RestoreSnapshot(float item_x, float item_y, const CollisionGrid &collisionGrid,
						 Vector<Vector<int>> &grid, Vector<int> &current_tiles)
	{
		int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

		if (collisionGrid.radius > 0.0)
		{
			x1 = std::max(static_cast<int>(std::floor(item_x - collisionGrid.radius)), 0);
			x2 = std::min(static_cast<int>(std::floor(item_x + collisionGrid.radius)), Globals::mapGridWidth - 1);

			y1 = std::max(static_cast<int>(std::floor(item_y - collisionGrid.radius)), 0);
			y2 = std::min(static_cast<int>(std::floor(item_y + collisionGrid.radius)), Globals::mapGridHeight - 1);
		}
		else
		{
			x1 = std::max(static_cast<int>(std::floor(item_x - static_cast<float>(collisionGrid.gridX))), 0);
			x2 = std::min(static_cast<int>(std::floor(item_x + static_cast<float>(collisionGrid.gridX))), Globals::mapGridWidth - 1);

			y1 = std::max(static_cast<int>(std::floor(item_y - static_cast<float>(collisionGrid.gridY))), 0);
			y2 = std::min(static_cast<int>(std::floor(item_y + static_cast<float>(collisionGrid.gridY))), Globals::mapGridHeight - 1);
		}

		for (int x = x1; x <= x2; x++)
		{
			for (int y = y1; y <= y2; y++)
			{
				if (!current_tiles.empty())
				{
					grid[y][x] = current_tiles.front();
					current_tiles.erase(current_tiles.begin());
				}
			}
		}
	}

	CoordsSnapshot TakeCoordsSnapshot(
		const Pair<int, int> &start, const Pair<int, int> &end, Vector<Vector<int>> &grid)
	{
		int startX = start.first;
		int startY = start.second;
		int startValue = grid[startY][startX];
		grid[startY][startX] = Flags::CELL_COLLISION_MODE_OFF;

		int endX = end.first;
		int endY = end.second;
		int endValue = grid[endY][endX];

		if (endValue != Flags::CELL_COLLISION_MODE_FULL)
		{
			grid[endY][endX] = Flags::CELL_COLLISION_MODE_OFF;
		}

		return CoordsSnapshot(startX, startY, startValue, endX, endY, endValue);
	}

	void RestoreCoordsSnapshot(
		const CoordsSnapshot &coordsSnapshot, Vector<Vector<int>> &grid)
	{
		int startX, startY, startValue, endX, endY, endValue;

		startX = coordsSnapshot.startX;
		startY = coordsSnapshot.startY;
		startValue = coordsSnapshot.startValue;

		endX = coordsSnapshot.endX;
		endY = coordsSnapshot.endY;
		endValue = coordsSnapshot.endValue;

		if (startValue != 0)
		{
			grid[startY][startX] = startValue;
		}

		if (endValue != 0 && grid[endY][endX] != Flags::CELL_COLLISION_MODE_FULL)
		{
			grid[endY][endX] = endValue;
		}
	}

	Cells() = delete;
	~Cells() = delete;
};
} // namespace TGX

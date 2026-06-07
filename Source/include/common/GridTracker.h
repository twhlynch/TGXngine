#pragma once

#include "Core.h"

namespace WoS
{
struct GridTracker
{
	Map<int, std::tuple<int, int, int, int>> uids_grid;
	Map<String, int> cells_grid;

	GridTracker() = default;

	void Clear()
	{
		uids_grid.clear();
		cells_grid.clear();
	}
};
} // namespace WoS

#pragma once

#include "Core.h"
#include "DataStructures/QuadTree.h"
#include "Globals.h"
#include "GridTracker.h"
#include "PhysicsDefinitions.h"
#include "StringUtils.hpp"
#include "WorldState.h"
#include "common_export.h"

namespace WoS
{
class Physics
{
private:
	Map<String, Unique<QuadTree>> quadTrees;
	GridTracker gridTracker;

	Physics() = default;
	~Physics() = default;

public:
	COMMON_API static Physics &GetInstance();

	Physics(const Physics &) = delete;
	Physics &operator=(const Physics &) = delete;

	Physics(Physics &&) = delete;
	Physics &operator=(Physics &&) = delete;

	void Add(const Set<String> &groups)
	{
		WorldState &world = WorldState::GetInstance();
		for (const auto &group : groups)
		{
			if (!quadTrees.contains(group))
			{
				Boundary boundary(0, 0, static_cast<float>(world.GetMapGridWidth() * Globals::grid_size), static_cast<float>(world.GetMapGridHeight() * Globals::grid_size));

				quadTrees[group] = std::make_unique<QuadTree>(boundary);
			}
		}
	}

	void Update()
	{
		for (auto &[group, quadTree] : this->quadTrees)
		{
			quadTree->Clear();
		}

		WorldState &world = WorldState::GetInstance();

		for (const auto &item : world.items)
		{
			ItemInstance *itemInstance = item.get();

			if (!itemInstance)
			{
				continue;
			}

			for (const auto &group : itemInstance->GetGroups())
			{
				if (auto it = this->quadTrees.find(group); it != this->quadTrees.end())
				{
					it->second->Insert(itemInstance->GetUid(), itemInstance->GetX(), itemInstance->GetY());
				}
			}
		}
	}

	Vector<PointUID> Find(const Set<String> &groups, const Boundary &range)
	{
		Set<PointUID> foundSet;

		for (const auto &group : groups)
		{
			auto it = quadTrees.find(group);
			if (it != quadTrees.end())
			{
				it->second->Query(range, foundSet);
			}
			else
			{
				Log::Print(StringConcat("Physics: No quadtree found for group: ", group));
			}
		}

		Vector<PointUID> foundUnits(foundSet.begin(), foundSet.end());
		return foundUnits;
	}

	void CleanQuadTree()
	{
		for (auto &[group, quadTree] : quadTrees)
		{
			quadTree->Clear();
		}
		quadTrees.clear();
	}

	GridTracker &GetGridTracker()
	{
		return gridTracker;
	}

	const GridTracker &GetGridTracker() const
	{
		return gridTracker;
	}

	void Clear()
	{
		gridTracker.Clear();
	}

	void Show() const
	{
		Log::Print("Physics: Current QuadTree Groups:");
		if (quadTrees.empty())
		{
			Log::Print("- (none)");
		}
		else
		{
			for (const auto &[group, quadTree] : quadTrees)
			{
				Log::Print(StringConcat("- ", group));
				Log::Print(StringConcat("QuadTrees size: ", QuadTree::Size()));
			}
		}
	}
};
} // namespace WoS

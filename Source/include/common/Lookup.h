#pragma once

#include "WorldState.h"

namespace WoS
{
struct LookUp
{
	void static Add(int uid)
	{
		WorldState &world = WorldState::GetInstance();
		world.SetLookup(uid, static_cast<int>(world.items.size()));
	}

	int static Get(int uid)
	{
		WorldState &world = WorldState::GetInstance();

		int index = world.GetLookup()[uid];

		if (index >= static_cast<int>(world.items.size()))
		{
			index = 0;
		}

		if (uid == world.items[index]->GetUid())
		{
			return index;
		}

		for (size_t i = 0; i < world.items.size(); i++)
		{
			if (world.items[i]->GetUid() == uid)
			{
				world.GetLookup()[uid] = static_cast<int>(i);

				return static_cast<int>(i);
			}
		}

		return -1;
	}

	void static Set(int uid, int index)
	{
		WorldState &world = WorldState::GetInstance();
		world.GetLookup()[uid] = index;
	}
};
} // namespace WoS

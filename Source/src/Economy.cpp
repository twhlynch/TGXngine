#include "Economy.h"
#include "Logs.h"
#include "WorldState.h"

namespace TGX
{
Economy::Economy(
	FNPTR_ECONOMY_AWAKE awake,
	FNPTR_ECONOMY_START start,
	FNPTR_ECONOMY_UPDATE update,
	FNPTR_ECONOMY_DRAW draw,
	FNPTR_ECONOMY_CLEAR clear,
	FNPTR_ECONOMY_DELETE _delete)
	: awake(awake), start(start), update(update),
	  draw(draw), clear(clear), _delete(_delete)
{
	Log::Success("Economy Wrapper Created");
}

void Economy::Awake(String name, int startingCash)
{
	Log::Info("Economy Awake calling module for: " + name);

	if (awake)
	{
		this->economyInstance = awake(std::move(name), startingCash);

		if (this->economyInstance)
		{
			WorldState &world = WorldState::GetInstance();
			world.economies.emplace_back(Unique<EconomyInstance>(this->economyInstance));

			world.SetCash(startingCash);
		}
		else
		{
			Log::Error("Failed to create EconomyInstance for: " + name);
		}
	}
}

void Economy::Start()
{
	if (start)
	{
		start();
	}
}

void Economy::Update()
{
	if (update && economyInstance)
	{
		update(economyInstance);
	}
}

void Economy::Draw()
{
	if (draw)
	{
		draw();
	}
}

void Economy::Clear()
{
	if (clear)
	{
		clear();
	}
}

void Economy::Delete()
{
	Log::Info("Economy Delete");
	if (_delete)
	{
		_delete();
	}
}
} // namespace TGX

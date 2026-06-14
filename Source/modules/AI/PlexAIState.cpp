#include "AIStates.h"
#include "Core.h"
#include "Logs.h"
#include "Orders.h"
#include "WorldState.h"

namespace WoS
{
void PlexAIState::Awake()
{
}

void PlexAIState::Start()
{
	Log::Print("AI Start");
}

void PlexAIState::Update()
{
	WorldState &world = WorldState::GetInstance();

	for (size_t i = 0; i < world.items.size(); i++)
	{
		if (world.items[i]->GetTeam() != world.GetTeam() && world.items[i]->GetOrders()->order == Orders::Order::None)
		{
			world.items[i]->SetOrders(Orders::Order::SearchAndDestroy);
		}
	}
}
} // namespace WoS

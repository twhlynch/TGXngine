#include "WorldState.h"

namespace WoS
{
WorldState &WorldState::GetInstance()
{
	static WorldState world;
	return world;
}
} // namespace WoS

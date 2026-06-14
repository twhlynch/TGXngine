#include "WorldState.h"

namespace TGX
{
WorldState &WorldState::GetInstance()
{
	static WorldState world;
	return world;
}
} // namespace TGX

#include "Physics.h"

namespace WoS
{
Physics &Physics::GetInstance()
{
	static Physics physics;
	return physics;
}
} // namespace WoS

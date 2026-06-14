#include "Physics.h"

namespace TGX
{
Physics &Physics::GetInstance()
{
	static Physics physics;
	return physics;
}
} // namespace TGX

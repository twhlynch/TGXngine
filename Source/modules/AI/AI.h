#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include "AIStates.h"
#include "WorldState.h"

using namespace nlohmann;

namespace TGX
{
// Declared as extern so the compiler knows it exists without allocating memory here
extern Vector<AIState *> activeOpponentStates;
} // namespace TGX

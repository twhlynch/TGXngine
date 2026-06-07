#pragma once

#include <cstdint>

namespace WoS
{
enum class ItemStates : std::uint8_t
{
	Stand,
	Moving,
	Attacking,
	Firing,
	Retreating,
	Capturing,
	Extracting,
	Detouring,
	Flying,
	Sailing,
};
} // namespace WoS

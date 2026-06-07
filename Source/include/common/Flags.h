#pragma once

namespace WoS
{
struct Flags
{
	inline static const int CELL_COLLISION_MODE_OFF = 0;
	inline static const int CELL_COLLISION_MODE_SOFT = 1;
	inline static const int CELL_COLLISION_MODE_WEAK = 10;
	inline static const int CELL_COLLISION_MODE_MEDIUM = 100;
	inline static const int CELL_COLLISION_MODE_HARD = 1000;
	inline static const int CELL_COLLISION_MODE_FULL = 10000;

	inline static const int CELL_COLLISION_MODE_SOFT_LIMIT = 0;
	inline static const int CELL_COLLISION_MODE_MEDIUM_LIMIT = 1;

	inline static const int LAYER_UNLOCKED = 0;
	inline static const int LAYER_SUBMERGE_LOCKED = 1;
	inline static const int LAYER_SURFACE_LOCKED = 2;
	inline static const int LAYER_AIR_LOCKED = 3;

	inline static const int FOG_X = 0;
	inline static const int FOG_O = 1;
	inline static const int FOG_NW = 2;
	inline static const int FOG_NE = 3;
	inline static const int FOG_SW = 4;
	inline static const int FOG_SE = 5;
	inline static const int FOG_N = 6;
	inline static const int FOG_W = 7;
	inline static const int FOG_E = 8;
	inline static const int FOG_S = 9;
};
} // namespace WoS

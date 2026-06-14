#pragma once

#include "Core.h"

namespace TGX
{
struct Globals
{
	const static int grid_size = 20;

	static inline int mapGridWidth = 0;
	static inline int mapGridHeight = 0;

	const static int main_interface_height = 80;

	const static int canvasWidth = 1040;
	const static int canvasHeight = 720;

	const static int OFFSCREEN_X = -1000;
	const static int OFFSCREEN_Y = -1000;

	static inline float mapOffsetX = 0;
	static inline float mapOffsetY = 0;

	static inline int NAVIGATION_GROUP_MOVE_TO_OFFSET = 3;

	static String imagePath;

	static inline unsigned int targetFPS = 60;
	static inline bool verticalSync = true;
};
} // namespace TGX

#pragma once

namespace WoS
{
struct CollisionGrid
{
	int gridX = 0;
	int gridY = 0;
	float radius = 0.0;
};

struct CollisionCoords
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int cellMode = 0;
};

struct CoordsSnapshot
{
	int startX = 0;
	int startY = 0;
	int startValue = 0;
	int endX = 0;
	int endY = 0;
	int endValue = 0;
};
} // namespace WoS

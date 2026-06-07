#pragma once

struct NavigationGroup
{
	int x;
	int y;
	int n;
};

struct DirectionGroup
{
	int id;
	int direction;
};

struct WayPoint
{
	int x;
	int y;
	int locked;
};

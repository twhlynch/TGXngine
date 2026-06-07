#include "Grid.h"
#include "Cells.h"
#include "Globals.h"
#include "Logs.h"
#include "Navigation.h"
#include "Window.h"

namespace WoS
{
Grid::Grid(json &level, json &obstruction_json)
{
	Globals::mapGridWidth = level["mapGridWidth"];
	Globals::mapGridHeight = level["mapGridHeight"];

	GenerateCurrentMapGrid();
	SetMapLookupTable(level, obstruction_json);
	SetCollisionTilesToGrid(level, obstruction_json);
	SetMapLookupTableToGrid(obstruction_json);

	Cells::Init();
}

Grid::~Grid() = default;

void Grid::GenerateCurrentMapGrid()
{
	currentMapTerrainGrid.resize(Globals::mapGridHeight, Vector<int>(Globals::mapGridWidth, 0));
	currentMapIsleGrid.resize(Globals::mapGridHeight, Vector<int>(Globals::mapGridWidth, 0));

	WorldState &world = WorldState::GetInstance();
	world.currentTerrainMapLookupTable.resize(Globals::mapGridHeight, Vector<int>(Globals::mapGridWidth, 0));
}

void Grid::SetMapLookupTable(json & /*level*/, json &obstruction_json)
{
	json mapTable = json();

	if (obstruction_json["singleplayer"].contains("mapTable"))
	{
		mapTable = obstruction_json["singleplayer"]["mapTable"];

		int mapTableIndex = 0;
		currentMapTable.reserve(mapTable.size());

		while (true)
		{
			String key = std::to_string(mapTableIndex);

			if (!mapTable.contains(key))
			{
				break;
			}

			currentMapTable.push_back(std::move(mapTable[key]));
			mapTableIndex++;
		}
	}
	else
	{
		Log::Error("mapTable is missing");
	}
}

void Grid::SetCollisionTilesToGrid(json & /*level*/, json &obstruction_json)
{
	const json *mapObstructedTerrainGrid = nullptr;
	const json *mapObstructedIsleGrid = nullptr;

	if (obstruction_json["singleplayer"].contains("mapObstructedTerrain"))
	{
		mapObstructedTerrainGrid = &obstruction_json["singleplayer"]["mapObstructedTerrain"];
	}
	else
	{
		Log::Error("mapObstructedTerrain is missing");
	}

	if (obstruction_json["singleplayer"].contains("mapObstructedIsle"))
	{
		mapObstructedIsleGrid = &obstruction_json["singleplayer"]["mapObstructedIsle"];
	}
	else
	{
		Log::Error("mapObstructedIsle is missing");
	}

	if (mapObstructedTerrainGrid)
	{
		SetCollisionTerrianIsleTilesToGrid(*mapObstructedTerrainGrid, currentMapTerrainGrid);
	}

	if (mapObstructedIsleGrid)
	{
		SetCollisionTerrianIsleTilesToGrid(*mapObstructedIsleGrid, currentMapIsleGrid);
	}
}

void Grid::SetCollisionTerrianIsleTilesToGrid(const json &mapObstructed, Vector<Vector<int>> &currentMapGrid)
{
	for (const auto &obstruction : mapObstructed)
	{
		int x = 0;
		int y = 0;
		int n = 0;

		y = obstruction[0];
		x = obstruction[1];
		n = obstruction[2];

		do
		{
			n--;
			currentMapGrid[y][x] = 1;

			x++;

			if (x == Globals::mapGridWidth)
			{
				x = 0;
				y++;
			}

		} while (n != 0);
	}
}

void Grid::SetMapLookupTableToGrid(const json &obstruction_json)
{
	json mapLookupTable = nullptr;
	WorldState &world = WorldState::GetInstance();

	if (obstruction_json["singleplayer"].contains("mapLookup"))
	{
		mapLookupTable = obstruction_json["singleplayer"]["mapLookup"];

		for (const auto &obstruction : mapLookupTable)
		{
			int t = -1;
			int x = 0;
			int y = 0;
			int n = 0;

			t = obstruction[0];
			y = obstruction[1];
			x = obstruction[2];
			n = obstruction[3];

			do
			{
				n--;
				world.currentTerrainMapLookupTable[y][x] = t;

				x++;

				if (x == Globals::mapGridWidth)
				{
					x = 0;
					y++;
				}

			} while (n != 0);
		}
	}
}

void Grid::BuildPassableGrid()
{
	WorldState &world = WorldState::GetInstance();
	world.currentTerrainMapPassableGrid.assign(Globals::mapGridHeight, Vector<int>(Globals::mapGridWidth, 0));
	world.currentIsleMapPassableGrid.assign(Globals::mapGridHeight, Vector<int>(Globals::mapGridWidth, 0));

	for (int y = 0; y < Globals::mapGridHeight; y++)
	{
		for (int x = 0; x < Globals::mapGridWidth; x++)
		{
			if (currentMapTerrainGrid[y][x] == 1)
			{
				world.currentTerrainMapPassableGrid[y][x] = Flags::CELL_COLLISION_MODE_FULL;
			}

			if (currentMapIsleGrid[y][x] == 1)
			{
				world.currentIsleMapPassableGrid[y][x] = Flags::CELL_COLLISION_MODE_MEDIUM;
			}
		}
	}

	Navigation::CreateWayPoints();
}

void Grid::Draw()
{
	const float cellSize = 20.0f;

	sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
	cellShape.setFillColor(sf::Color(255, 0, 0, 100));

	WorldState &world = WorldState::GetInstance();
	Window &window = Window::GetInstance();

	for (size_t y = 0; y < world.currentTerrainMapPassableGrid.size(); ++y)
	{
		for (size_t x = 0; x < world.currentTerrainMapPassableGrid[y].size(); ++x)
		{
			if (world.currentTerrainMapPassableGrid[y][x] != Flags::CELL_COLLISION_MODE_OFF)
			{
				auto posX = ((static_cast<float>(x) * cellSize) + static_cast<float>(world.GetMapXOffset()));
				auto posY = ((static_cast<float>(y) * cellSize) + static_cast<float>(world.GetMapYOffset()));

				cellShape.setPosition(posX, posY);
				window.Draw(cellShape);
			}
		}
	}
}
} // namespace WoS

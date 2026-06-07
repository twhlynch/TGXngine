#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Core.h"

using namespace nlohmann;

namespace WoS
{
class Grid
{
public:
	Grid(json &level, json &obstruction_json);
	~Grid();
	void Draw();
	void BuildPassableGrid();

private:
	void GenerateCurrentMapGrid();
	void SetMapLookupTable(json &level, json &obstruction_json);
	void SetCollisionTilesToGrid(json &level, json &obstruction_json);
	void SetCollisionTerrianIsleTilesToGrid(const json &mapObstructed, Vector<Vector<int>> &currentMapGrid);
	void SetMapLookupTableToGrid(const json &obstruction_json);

	sf::RectangleShape debugDrawCells;
	Vector<String> currentMapTable;
	Vector<Vector<int>> currentMapTerrainGrid;
	Vector<Vector<int>> currentMapIsleGrid;
};
} // namespace WoS

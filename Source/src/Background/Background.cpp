#include "Background.h"
#include <cmath>
#include "Globals.h"
#include "Window.h"
#include "WorldState.h"

namespace WoS
{
Background::Background(json &level)
{
	WorldState &world = WorldState::GetInstance();

	startingTile = 0;
	Globals::mapGridWidth = level["mapGridWidth"];
	Globals::mapGridHeight = level["mapGridHeight"];

	backgroundWidth = static_cast<int>(level["mapGridWidth"]) * Globals::grid_size;
	backgroundHeight = static_cast<int>(level["mapGridHeight"]) * Globals::grid_size;

	world.UpdateMapXOffset(level["backgroundOffsetX"]);
	world.UpdateMapYOffset(level["backgroundOffsetY"]);

	world.SetNumberOfHorizontalTiles(level["numberOfHorizontalTiles"]);
	world.SetNumberOfVerticalTiles(level["numberOfVerticalTiles"]);

	AssignTileNames(String(level["mapImage"]));
	LoadBackgroundTiles();
}

Background::~Background() = default;

void Background::LoadBackgroundTiles()
{
	backgroundTextures.reserve(tileNames.size());
	backgroundSprites.reserve(tileNames.size());

	for (const auto &tileName : tileNames)
	{
		auto texture = std::make_unique<sf::Texture>();
		if (!texture->loadFromFile(tileName))
		{
			Log::Warning("Cannot load image: " + tileName);
			continue;
		}

		texture->setSmooth(false);
		backgroundTextures.push_back(std::move(texture));

		auto sprite = std::make_unique<sf::Sprite>();
		sprite->setTexture(*backgroundTextures.back());

		sprite->setTextureRect(sf::IntRect(0, 0, rotationXLimit + 1, rotationYLimit + 1));

		backgroundSprites.push_back(std::move(sprite));
	}

	WorldState &world = WorldState::GetInstance();
	int totalTiles = world.GetNumberOfHorizontalTiles() * world.GetNumberOfVerticalTiles();

	tileAnchors.clear();
	tileAnchors.reserve(totalTiles);

	for (int l = 0; l < world.GetNumberOfHorizontalTiles(); l++)
	{
		for (int k = 0; k < world.GetNumberOfVerticalTiles(); k++)
		{
			float x = static_cast<float>(k * rotationXLimit);
			float y = static_cast<float>((l * rotationYLimit) + 80);
			tileAnchors.push_back(sf::Vector2f(x, y));
		}
	}

	SyncPosition();
}

void Background::SyncPosition()
{
	for (size_t i = 0; i < backgroundSprites.size(); i++)
	{
		float finalX = tileAnchors[i].x - Globals::mapOffsetX;
		float finalY = tileAnchors[i].y - Globals::mapOffsetY;

		backgroundSprites[i]->setPosition(std::round(finalX), std::round(finalY));
	}
}

void Background::AssignTileNames(const String &mapImages)
{
	WorldState &world = WorldState::GetInstance();
	int totalTiles = world.GetNumberOfVerticalTiles() * world.GetNumberOfHorizontalTiles();
	tileNames.reserve(totalTiles);

	for (int i = 0; i < totalTiles; i++)
	{
		tileNames.emplace_back(mapImages + std::to_string(i) + ".png");
	}
}

void Background::Draw()
{
	Window &window = Window::GetInstance();
	for (auto &sprite : backgroundSprites)
	{
		window.Draw(*sprite);
	}
}

int Background::GetWidth() const
{
	return backgroundWidth;
}

int Background::GetHeight() const
{
	return backgroundHeight;
}
} // namespace WoS

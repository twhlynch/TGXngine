#pragma once

#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include "ItemInstance.h"
#include "Window.h"

namespace WoS
{
ItemInstance *globalItem;
Map<String, Function<ItemInstance *()>> buildingStateRegistry;

struct Building
{
	String name;

	float radius = 0;
	int frames = 0;
	int speed = 0;
	int turnSpeed = 0;
	int topSpeed = 0;
	int passableGridWidth = 0;
	int passableGridHeight = 0;
	bool animation = false;
	int animationCount = 0;
	int animationLimit = 0;
	int animationSpeed = 0;
	int animationSpeedLimit = 0;
	int animationSlowSpeed = 0;
	int animationSlowSpeedLimit = 0;
	int directions = 0;
};

class Buildings
{
private:
	sf::RectangleShape *selectionRectangle;

public:
	Buildings(ItemInstance *itemInstance)
	{
		CreateSelectionRectangle(itemInstance->GetX(), itemInstance->GetY(), itemInstance->GetWidth(), itemInstance->GetHeight());
	}

	~Buildings()
	{
		delete selectionRectangle;
	}

	void Draw(ItemInstance *itemInstance, Vector<sf::Sprite *> *spritesRef)
	{
		Window &window = Window::GetInstance();

		if (itemInstance->IsSelected())
		{
			window.Draw(*selectionRectangle);
		}

		window.Draw(*(*spritesRef)[itemInstance->GetFrame()]);
	}

	void Update(ItemInstance *itemState, Vector<sf::Sprite *> * /*spritesRef*/)
	{
		WorldState &world = WorldState::GetInstance();
		selectionRectangle->setPosition(
			((itemState->GetX() * 20.0f) + static_cast<float>(world.GetMapXOffset())),
			((itemState->GetY() * 20.0f) + static_cast<float>(world.GetMapYOffset())));
	}

private:
	void CreateSelectionRectangle(float /*x*/, float /*y*/, int width, int height)
	{
		selectionRectangle = new sf::RectangleShape();
		selectionRectangle->setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
		selectionRectangle->setFillColor(sf::Color(255, 216, 0, 51));
		selectionRectangle->setOutlineColor(sf::Color(255, 255, 0, 128));
		selectionRectangle->setOutlineThickness(1);
	}
};

using FNPTR_INIT = void (*)();

Map<int, Buildings *> buildings;
} // namespace WoS

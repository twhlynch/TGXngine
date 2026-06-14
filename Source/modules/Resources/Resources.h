#pragma once

#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include "Globals.h"
#include "ResourceInstance.h"
#include "ResourcesStates.h"
#include "Window.h"

namespace TGX
{
ResourceInstance *globalResource;

class Resources
{
public:
	Resources(ResourceInstance *resourcesState)
	{
	}

	~Resources() = default;

	void draw(ResourceInstance *resourcesState, std::vector<sf::Sprite *> *spritesRef)
	{
		Window &window = Window::GetInstance();

		window.Draw(*(*spritesRef)[resourcesState->GetFrame()]);
	}
};

Map<int, Unique<Resources>> resources;
} // namespace TGX

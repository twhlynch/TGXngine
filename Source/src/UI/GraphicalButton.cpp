#include "GraphicalButton.h"
#include "Enums.h"
#include "Renderer.h"
#include "SFML/Graphics/Texture.hpp"
#include "Window.h"
#include "WorldState.h"

namespace WoS
{
GraphicalButton::GraphicalButton()
{
	Log::Success("Graphical Button Created");
}

bool GraphicalButton::Click()
{
	WorldState &world = WorldState::GetInstance();
	if (Intersect(world.GetMouseX(), world.GetMouseY(), x, y, x + static_cast<float>(width), y + static_cast<float>(height)))
	{
		if (action == UIAction::None || value == "")
		{
			return false;
		}

		Log::Info("Graphical Button - Action:" + UIActionToString(action) + ", Value: " + value);

		Renderer::GetInstance().functions[action](Renderer::GetInstance(), value);
		return true;
	}

	return false;
}

void GraphicalButton::Draw()
{
	Window &window = Window::GetInstance();
	window.Draw(sprite);
}

void GraphicalButton::SetButton(const String &text, UIAction newAction, const String &newValue, float newX, float newY, int /*newWidth*/, int /*newHeight*/)
{
	sf::Image image;
	if (!(image.loadFromFile(text)))
	{
		Log::Error("Cannot load image: " + text);
	}

	spriteTexture = std::make_unique<sf::Texture>();
	spriteTexture->loadFromImage(image);
	sprite.setTexture(*spriteTexture);

	this->action = newAction;
	this->value = newValue;

	this->x = newX;
	this->y = newY;

	this->width = static_cast<int>(spriteTexture->getSize().x);
	this->height = static_cast<int>(spriteTexture->getSize().y);

	sprite.setPosition(this->x, this->y);
}

void GraphicalButton::SetButton(
	const String &text, UIAction inAction, const String &inValue, const String &alignment,
	float inX, float inY, int /*newWidth*/, int /*newHeight*/, int xOffset, int yOffset)
{
	sf::Image image;
	if (!(image.loadFromFile(text)))
	{
		Log::Error("Cannot load image: " + text);
	}

	spriteTexture = std::make_unique<sf::Texture>();
	spriteTexture->loadFromImage(image);
	sprite.setTexture(*spriteTexture);

	this->x = inX;
	this->y = inY;

	Alignment alignmentValue = AlignmentFromString(alignment);

	if (alignmentValue == Alignment::Horizontal || alignmentValue == Alignment::Both)
	{
		this->x += static_cast<float>(xOffset);
	}

	if (alignmentValue == Alignment::Vertical || alignmentValue == Alignment::Both)
	{
		this->y += static_cast<float>(yOffset);
	}

	sprite.setPosition(this->x, this->y);

	this->action = inAction;
	this->value = inValue;

	this->width = static_cast<int>(spriteTexture->getSize().x);
	this->height = static_cast<int>(spriteTexture->getSize().y);
}

void GraphicalButton::Clear()
{
}
} // namespace WoS

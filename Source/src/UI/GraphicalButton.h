#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

namespace WoS
{
class GraphicalButton : public Button
{
private:
	sf::Sprite sprite;
	Unique<sf::Texture> spriteTexture;

public:
	GraphicalButton();
	~GraphicalButton() override = default;
	bool Click() override;
	void Draw() override;
	void SetButton(const String &text, UIAction action, const String &value, float x, float y, int width, int height) override;
	void SetButton(const String &text, UIAction action, const String &value, const String &alignment, float x, float y, int width, int height, int xOffset, int yOffset) override;
	void Clear() override;
};
} // namespace WoS

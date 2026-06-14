#pragma once

#include "Button.h"

namespace TGX
{
class TextButton : public Button
{
private:
	sf::Font font;
	sf::Text drawText;
	String text;
	int size;
	int outline_size;
	bool isHover;
	bool was_Font_Loaded;
	unsigned int textColour;
	unsigned int outlineColour;
	unsigned int hoverColour;

public:
	TextButton();
	~TextButton() override;
	bool Click() override;
	void Draw() override;
	void SetButton(const String &text, UIAction action, const String &value, float x, float y, int width, int height) override;
	void SetButton(const String &text, UIAction action, const String &value, const String &alignment, float x, float y, int width, int height, int xOffset, int yOffset) override;
	void SetColour(const String &colour);
	void SetOutlineColour(const String &colour);
	void CreateTextFontSize();
	void SetHover(const String &color);
	void SetText(const String &text);
	void SetFont(const String &font_file);
	void SetFontStyle(String &font_style);
	void SetSize(int size);
	void SetOutlineSize(unsigned int size);
	void Clear() override;
};
} // namespace TGX

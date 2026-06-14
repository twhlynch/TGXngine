#pragma once

#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include "Enums.h"

namespace TGX
{
class Button
{
protected:
	UIAction action = UIAction::None;
	String value;
	float x;
	float y;
	int width;
	int height;

public:
	virtual ~Button() = default;
	virtual bool Click() = 0;
	virtual void Draw() = 0;
	virtual void SetButton(const String &text, UIAction action, const String &value, float x, float y, int width, int height) = 0;
	virtual void SetButton(const String &text, UIAction action, const String &value, const String &alignment, float x, float y, int width, int height, int xOffset, int yOffset) = 0;
	virtual void Clear() = 0;
};
} // namespace TGX

#pragma once

#include "SFML/Window/Keyboard.hpp"

using Key = sf::Keyboard::Key;

namespace WoS
{
class Keyboard
{
private:
	Keyboard();
	~Keyboard() = default;

public:
	static Keyboard &GetInstance();

	Keyboard(const Keyboard &) = delete;
	Keyboard &operator=(const Keyboard &) = delete;

	Keyboard(Keyboard &&) = delete;
	Keyboard &operator=(Keyboard &&) = delete;

	void KeyPressed(Key code);
};
} // namespace WoS

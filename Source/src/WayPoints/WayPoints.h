#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace WoS
{
class WayPoints
{
public:
	WayPoints();
	~WayPoints() = default;
	void Draw();
};
} // namespace WoS

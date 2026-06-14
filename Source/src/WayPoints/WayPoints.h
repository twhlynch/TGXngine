#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace TGX
{
class WayPoints
{
public:
	WayPoints();
	~WayPoints() = default;
	void Draw();
};
} // namespace TGX

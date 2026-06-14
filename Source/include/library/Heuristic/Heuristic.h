#pragma once

#include <cmath>
#include <functional>
#include <numbers>
#include "Core.h"

namespace TGX
{
enum class HeuristicType : std::uint8_t
{
	Manhattan,
	Euclidean,
	Octile,
	Chebyshev
};

using HeuristicFunc = std::function<float(float, float, float, float)>;

inline float Manhattan(float startX, float startY, float endX, float endY)
{
	float dx = std::abs(startX - endX);
	float dy = std::abs(startY - endY);
	return dx + dy;
}

inline float Euclidean(float startX, float startY, float endX, float endY)
{
	float x = startX - endX;
	float y = startY - endY;
	return std::sqrt((x * x) + (y * y));
}

inline float Octile(float startX, float startY, float endX, float endY)
{
	float dx = startX - endX;
	float dy = startY - endY;
	const float F = std::numbers::sqrt2_v<float> - 1.0f;
	return (dx < dy) ? (F * dx) + dy : (F * dy) + dx;
}

inline float Chebyshev(float startX, float startY, float endX, float endY)
{
	float x = startX - endX;
	float y = startY - endY;
	return static_cast<float>(std::max(x, y));
}

// FIXME: Initialization of 'heuristicFunctions' with static storage duration may throw an exception that cannot be caught
inline Map<HeuristicType, Function<float(float, float, float, float)>> heuristicFunctions = { // NOLINT(cert-err58-cpp)
	{HeuristicType::Manhattan, [](float x1, float y1, float x2, float y2) {
		 return Manhattan(x1, y1, x2, y2);
	 }},
	{HeuristicType::Euclidean, [](float x1, float y1, float x2, float y2) {
		 return Euclidean(x1, y1, x2, y2);
	 }},
	{HeuristicType::Octile, [](float x1, float y1, float x2, float y2) {
		 return Octile(x1, y1, x2, y2);
	 }},
	{HeuristicType::Chebyshev, [](float x1, float y1, float x2, float y2) {
		 return Chebyshev(x1, y1, x2, y2);
	 }}};
} // namespace TGX

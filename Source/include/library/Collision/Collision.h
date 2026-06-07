#pragma once

#include <cmath>
#include <limits>
#include "Core.h"

namespace WoS
{
inline float SATCollision(const Array<float, 8> &poly1, const Array<float, 8> &poly2)
{
	const Array<float, 8> &p1 = poly1;
	const Array<float, 8> &p2 = poly2;

	float overlap = INFINITY;

	for (size_t a = 0; a < p1.size(); a = a + 2)
	{
		float axisProjX = p1[(a + 2) % p1.size()] - p1[a];
		float axisProjY = p1[(a + 3) % p1.size()] - p1[a + 1];

		float d = sqrt((axisProjX * axisProjX) + (axisProjY * axisProjY));

		axisProjX = axisProjX / d;
		axisProjY = axisProjY / d;

		float minR1 = std::numeric_limits<float>::infinity();
		float maxR1 = -std::numeric_limits<float>::infinity();

		for (size_t p = 0; p < p1.size(); p = p + 2)
		{
			float q = (p1[p] * axisProjX) + (p1[p + 1] * axisProjY);
			minR1 = std::min(minR1, q);
			maxR1 = std::max(maxR1, q);
		}

		float minR2 = std::numeric_limits<float>::infinity();
		float maxR2 = -std::numeric_limits<float>::infinity();

		for (size_t p = 0; p < p2.size(); p = p + 2)
		{
			float q = (p2[p] * axisProjX) + (p2[p + 1] * axisProjY);
			minR2 = std::min(minR2, q);
			maxR2 = std::max(maxR2, q);
		}

		overlap = std::min(std::min(maxR1, maxR2) - std::max(minR1, minR2), overlap);
	}

	return overlap;
}
} // namespace WoS

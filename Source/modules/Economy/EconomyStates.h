#pragma once
#include "Core.h"

namespace WoS
{
struct ResourceRule
{
	float rate;
	float threshold;
	int value;
};

struct EconomyState
{
	Map<String, ResourceRule> resourceRules = {
		{"oil", {20.0f, 1000.0f, 1000}},
		{"water", {10.0f, 500.0f, 500}},
		{"copper", {5.0f, 250.0f, 750}}};
};

static EconomyState globalEconomyState;
} // namespace WoS

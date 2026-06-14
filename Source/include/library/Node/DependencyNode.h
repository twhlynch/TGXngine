#pragma once

#include <utility>
#include "Core.h"

namespace TGX
{
struct DependencyNode
{
	String name;
	String type;
	int cost;
	int powerUsage;
	int powerTotal;

	Vector<DependencyNode *> dependents;

	DependencyNode(String n, String t, int c, int pUsage, int pTotal) : name(std::move(n)), type(std::move(t)), cost(c), powerUsage(pUsage), powerTotal(pTotal) {}
};
} // namespace TGX

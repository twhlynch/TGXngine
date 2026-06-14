#pragma once

#include <nlohmann/json.hpp>
#include <cstddef>
#include "Core.h"
#include "Logs.h"
#include "Node/DependencyNode.h"
#include "StringUtils.hpp"

using namespace nlohmann;

namespace TGX
{
class DependencyTree
{
public:
	DependencyNode *root;

	DependencyTree(DependencyNode *rootNode) : root(rootNode) {}
	~DependencyTree()
	{
		DeleteTree(root);
	}

	static DependencyNode *BuildNodeFromJson(const json &nodeJson)
	{
		auto *node = new DependencyNode(
			nodeJson["name"].get<String>(),
			nodeJson["type"].get<String>(),
			nodeJson["cost"].get<int>(),
			nodeJson["power_usage"].get<int>(),
			nodeJson["power_total"].get<int>());

		for (const auto &depJson : nodeJson["dependencies"])
		{
			DependencyNode *dependentNode = BuildNodeFromJson(depJson);
			node->dependents.push_back(dependentNode);
		}

		return node;
	}

	DependencyNode *FindParent(DependencyNode *current, const std::string &childName)
	{
		if (!current)
		{
			return nullptr;
		}

		for (auto *dependent : current->dependents)
		{
			if (dependent->name == childName)
			{
				return current;
			}

			DependencyNode *parent = FindParent(dependent, childName);

			if (parent)
			{
				return parent;
			}
		}

		return nullptr;
	}

	DependencyNode *GetParent(const String &childName)
	{
		if (!root || root->name == childName)
		{
			return nullptr;
		}

		return FindParent(root, childName);
	}

	DependencyNode *GetNodeByName(const String &nodeName, DependencyNode *currentNode) const
	{
		if (!currentNode)
		{
			return nullptr;
		}

		if (currentNode->name == nodeName)
		{
			return currentNode;
		}

		for (const auto &dependdent : currentNode->dependents)
		{
			DependencyNode *foundNode = GetNodeByName(nodeName, dependdent);

			if (foundNode)
			{
				return foundNode;
			}
		}

		return nullptr;
	}

	Vector<Pair<String, int>> GetDependencies(const String &nodeName) const
	{
		DependencyNode *node = GetNodeByName(nodeName, root);
		Vector<Pair<String, int>> dependencies;

		if (!node)
		{
			Log::Error(StringConcat("Node \"", nodeName, "\" not found in the tree."));
			return dependencies;
		}

		CollectDependencies(node, dependencies, 0);
		return dependencies;
	}

	void CollectDependencies(const DependencyNode *node, Vector<Pair<String, int>> &dependencies, int depth) const
	{
		if (!node)
		{
			return;
		}

		for (const auto &dependent : node->dependents)
		{
			dependencies.emplace_back(dependent->name, depth + 1);
			CollectDependencies(dependent, dependencies, depth + 1);
		}
	}

	bool ResolveDependencies(DependencyNode *node, Set<String> &resolved, Vector<String> &buildOrder)
	{
		if (!node)
		{
			return true;
		}

		if (resolved.contains(node->name))
		{
			return true;
		}

		for (auto *dependent : node->dependents)
		{
			if (!ResolveDependencies(dependent, resolved, buildOrder))
			{
				return false;
			}
		}

		resolved.insert(node->name);
		buildOrder.push_back(node->name);

		return true;
	}

	void DisplayTree(DependencyNode *node, int depth = 0)
	{
		if (!node)
		{
			return;
		}

		Log::Print(StringConcat(std::string(static_cast<size_t>(depth * 4), ' '), "- ", node->name, " (", node->type, ", Cost: ", node->cost, ", Power Usage: ", node->powerUsage, ", Power Total: ", node->powerTotal, ")"));

		for (auto *dependent : node->dependents)
		{
			DisplayTree(dependent, depth + 1);
		}
	}

	bool GetBuildOrder(Vector<String> &buildOrder)
	{
		Set<String> resolved;

		return ResolveDependencies(root, resolved, buildOrder);
	}

	bool HasCycle(DependencyNode *node, Set<String> &visited, Set<String> &stack)
	{
		if (!node)
		{
			return false;
		}

		if (stack.contains(node->name))
		{
			return true;
		}

		stack.insert(node->name);

		for (auto *dependent : node->dependents)
		{
			if (HasCycle(dependent, visited, stack))
			{
				return true;
			}
		}

		stack.erase(node->name);

		return false;
	}

	bool IsAcyclic()
	{
		Set<String> visited;
		Set<String> stack;

		return !HasCycle(root, visited, stack);
	}

	void DeleteTree(DependencyNode *node)
	{
		if (!node)
		{
			return;
		}

		for (auto *dependent : node->dependents)
		{
			DeleteTree(dependent);
		}
	}
};
} // namespace TGX

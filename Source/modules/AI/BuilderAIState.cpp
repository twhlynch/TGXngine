#include "AI.h"
#include "AIStates.h"
#include "Core.h"
#include "Enums.h"
#include "Logs.h"
#include "StringUtils.hpp"
#include "Utils.hpp"
#include "WorldState.h"

namespace WoS
{

// Module-local storage structures for this state instance cleanly declared at namespace level
static Map<String, Ref<BuildNode>> masterBuildTemplates;
static Vector<Ref<BuildNode>> rootTechNodes;
static int globalBuildLimit = 6;

void BuilderAIState::Awake()
{
}

void BuilderAIState::Start()
{
	WorldState &world = WorldState::GetInstance();

	for (size_t i = 0; i < world.items.size(); i++)
	{
		if (!world.items[i])
		{
			continue;
		}

		// FIXED: Changed '!=' to '==' so the AI issues commands to its OWN buildings
		if (world.items[i]->GetTeam() == world.GetTeam() && world.items[i]->GetName() == "construction_facility")
		{
			Log::Print("AI construction_facility selected successfully.");

			// FIXED: Standardize entirely on your native String utilities to prevent cross-casting compilation errors
			String command = StringConcat("command:", "build");
			command += ",";

			String name = StringConcat("name:", "powerplant");
			command += name + ",";

			String type = StringConcat("type:", "buildings");
			command += type + ",";

			// Ensure world.items[i]->GetTeam() matches the expected type parameter of StringConcat
			String team = StringConcat("team:", world.items[i]->GetTeam());
			command += team + ",";

			String x = StringConcat("x:", std::to_string(RoundGridDown(75 * 20, 0, 20)));
			command += x + ",";

			String y = StringConcat("y:", std::to_string(RoundGridDown(60 * 20, -80, 20)));
			command += y;

			Log::Print(StringConcat("AI Command Generated: ", command));

			// Queue up the event frame natively
			world.gameEvents.emplace_back(UIAction::AddGameItem, command);
		}
	}
}

void BuilderAIState::Update()
{
}

void BuilderAIState::InitialiseMapTechTree(const nlohmann::json &aiOpponentData)
{
	Log::Print("BuilderAIState parsing map tech tree...");

	// 1. Clear out any residual data if re-entering a level
	masterBuildTemplates.clear();
	rootTechNodes.clear();

	// 2. Extract global configuration limits cleanly
	if (aiOpponentData.contains("buildLimit"))
	{
		globalBuildLimit = aiOpponentData["buildLimit"].get<int>();
	}

	if (!aiOpponentData.contains("techTree") || !aiOpponentData["techTree"].contains("nodes"))
	{
		Log::Warning("Provided AI opponent data lacks a valid techTree structure.");
		return;
	}

	const auto &jsonNodes = aiOpponentData["techTree"]["nodes"];

	// FIRST PASS: Allocate all BuildNodes and populate their raw values
	for (const auto &nodeJson : jsonNodes)
	{
		if (!nodeJson.contains("name"))
		{
			Log::Warning("Skipping invalid tech tree node entry missing a 'name' field.");
			continue;
		}

		auto node = std::make_shared<BuildNode>();
		node->name = nodeJson["name"].get<String>();
		node->role = nodeJson.value("role", "");
		node->cost = nodeJson.value("cost", 0);
		node->powerUsage = nodeJson.value("powerUsage", 0);
		node->buildTime = nodeJson.value("buildTime", 0);
		node->isRoot = nodeJson.value("isRoot", false);

		// Temporarily store children names to establish linkages in our second pass
		if (nodeJson.contains("children") && nodeJson["children"].is_array())
		{
			for (const auto &childName : nodeJson["children"])
			{
				node->childrenNames.push_back(childName.get<String>());
			}
		}

		// Cache the node in our master map registry
		masterBuildTemplates[node->name] = node;

		// Keep track of base starting points for immediate traversal
		if (node->isRoot)
		{
			rootTechNodes.push_back(node);
		}
	}

	// SECOND PASS: Reconstruct hierarchy by resolving string identifiers to direct references
	int linkedEdgesCount = 0;
	for (auto &[name, parentNode] : masterBuildTemplates)
	{
		for (const String &childName : parentNode->childrenNames)
		{
			// Verify the referenced child node actually exists in our data mapping
			auto it = masterBuildTemplates.find(childName);
			if (it != masterBuildTemplates.end())
			{
				Ref<BuildNode> &childNode = it->second;

				// Establish the explicit parent pointer reference link
				childNode->parent = parentNode;
				linkedEdgesCount++;
			}
			else
			{
				Log::Warning("Tech Tree Layout Mismatch: Node '" + name +
							 "' references missing child node target signature: '" + childName + "'");
			}
		}
	}

	Log::Success("Tech Tree Generation Complete: Successfully compiled " +
				 std::to_string(masterBuildTemplates.size()) + " nodes and mapped " +
				 std::to_string(linkedEdgesCount) + " structural pointer linkages.");

	DisplayTechTree();
}

void BuilderAIState::DisplayTechTree() const
{
	Log::Print("--------------------------------------------------");
	Log::Print("         LIVE AI TECH TREE VISUALIZATION          ");
	Log::Print("--------------------------------------------------");

	if (rootTechNodes.empty())
	{
		Log::Warning("Cannot display tech tree: No root nodes have been registered.");
		return;
	}

	// Process every independent tree root found in the configuration payload
	for (const auto &root : rootTechNodes)
	{
		PrintNodeRecursive(root, 0);
	}

	Log::Print("--------------------------------------------------");
}

void BuilderAIState::PrintNodeRecursive(const Ref<BuildNode> &node, int depth) const
{
	if (!node)
	{
		return;
	}

	// 1. Build a dynamic indentation indent visual based on tree depth
	String indentation = "";
	for (int i = 0; i < depth; ++i)
	{
		indentation += (i == depth - 1) ? "|-- " : "|   ";
	}

	// 2. Format details about this node
	String nodeInfo = indentation + node->name + " [" + node->role + "]";
	nodeInfo += " (Cost: " + std::to_string(node->cost) + ", Time: " + std::to_string(node->buildTime) + ")";

	Log::Print(nodeInfo);

	// 3. Traverse using our direct pointer layout map!
	for (const auto &[name, potentialChild] : masterBuildTemplates)
	{
		// FIXED: Direct evaluation check comparing the parent shared_ptr with the current node shared_ptr
		if (potentialChild && potentialChild->parent == node)
		{
			PrintNodeRecursive(potentialChild, depth + 1);
		}
	}
}

} // namespace WoS

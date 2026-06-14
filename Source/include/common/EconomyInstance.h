#pragma once

#include "Core.h"

namespace TGX
{
class EconomyInstance
{
private:
	String team = "none";
	int cash = 0;
	Map<String, float> resources;

public:
	EconomyInstance() = default;

	EconomyInstance(const EconomyInstance &) = delete;
	EconomyInstance &operator=(const EconomyInstance &) = delete;

	virtual ~EconomyInstance() = default;

	String GetTeam() const { return team; }
	void SetTeam(const String &inTeam) { team = inTeam; }

	int GetCash() const { return cash; }
	void SetCash(int inCash) { cash = inCash; }
	void AddCash(int amount) { cash += amount; }

	void AddResourceProgress(const String &resName, float amount)
	{
		resources[resName] += amount;
	}

	float GetResourceProgress(const String &resName)
	{
		return resources[resName];
	}

	void ConsumeResourceProgress(const String &resName, float threshold)
	{
		resources[resName] -= threshold;
	}
};
} // namespace TGX

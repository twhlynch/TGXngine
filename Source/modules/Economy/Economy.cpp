#include "Economy.h"
#include "Core.h"
#include "EconomyStates.h"
#include "Logs.h"
#include "module_interface.h"

namespace TGX
{
extern "C"
{
	MODULE_API void Init()
	{
		Log::Success("Economy Init");
	}

	MODULE_API EconomyInstance *Awake(const String &name, int startingCash)
	{
		Log::Success("Awake " + name + " with $" + std::to_string(startingCash));

		EconomyInstance *instance = new EconomyInstance();
		instance->SetTeam(name);
		instance->SetCash(startingCash);

		return instance;
	}

	MODULE_API void Start(const String &name, const String &resource)
	{
		Log::Success("Economy Start");
	}

	MODULE_API void Update(EconomyInstance *instance)
	{
		WorldState &world = WorldState::GetInstance();
		float deltaTime = world.GetDeltaTime();
		String teamName = instance->GetTeam();
		int cashEarnedThisTick = 0;

		for (auto &[resName, rules] : globalEconomyState.resourceRules)
		{
			int count = world.extractors[teamName][resName];

			float gathered = rules.rate * static_cast<float>(count) * deltaTime;
			instance->AddResourceProgress(resName, gathered);

			if (instance->GetResourceProgress(resName) >= rules.threshold)
			{
				instance->ConsumeResourceProgress(resName, rules.threshold);
				cashEarnedThisTick += rules.value;
			}
		}

		if (cashEarnedThisTick > 0)
		{
			instance->AddCash(cashEarnedThisTick);

			if (teamName == world.GetTeam())
			{
				world.SetCash(instance->GetCash());
			}
		}
	}

	MODULE_API void Draw()
	{
	}

	MODULE_API void Clear()
	{
		Log::Success("Clear Economy");
	}

	MODULE_API void Destroy()
	{
		Log::Success("Economy Destroy");
	}
}
} // namespace TGX

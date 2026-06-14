#pragma once

#include "Core.h"
#include "Enums.h"
#include "WorldState.h"

namespace TGX
{
class Trigger
{
public:
	virtual ~Trigger() = default;
	String type;

protected:
	UIAction action = UIAction::None;
	String value;

	void Action()
	{
		WorldState &world = WorldState::GetInstance();
		world.gameEvents.emplace_back(action, value);
	}

public:
	virtual bool Elapse() = 0;
};

class TimedTrigger : public Trigger
{
private:
	int interval;
	int interval_counter;
	bool repeat;

public:
	TimedTrigger(UIAction action, int interval, bool repeat);
	TimedTrigger(UIAction action, const String &value, int interval, bool repeat);
	bool Elapse() override;
};

class ConditionalTrigger : public Trigger
{
private:
	Function<bool()> conditionalFunction;

public:
	ConditionalTrigger(UIAction action, Function<bool()> conditionalFunction);
	ConditionalTrigger(UIAction action, const String &value, Function<bool()> conditionalFunction);
	bool Elapse() override;
};
} // namespace TGX

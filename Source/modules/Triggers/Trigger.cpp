#include "Trigger.h"
#include <functional>
#include <utility>

namespace WoS
{
TimedTrigger::TimedTrigger(UIAction action, int interval, bool repeat)
{
	this->action = action;
	this->value = "";
	this->interval = interval;
	this->repeat = repeat;
	interval_counter = interval;
}

TimedTrigger::TimedTrigger(UIAction action, const String &value, int interval, bool repeat)
{
	this->action = action;
	this->value = value;
	this->interval = interval;
	this->repeat = repeat;
	interval_counter = interval;
}

bool TimedTrigger::Elapse()
{
	if (interval_counter != 0)
	{
		interval_counter--;
	}
	else
	{
		Action();

		if (repeat)
		{
			this->interval_counter = interval;
		}
		else
		{
			return true;
		}
	}

	return false;
}

ConditionalTrigger::ConditionalTrigger(UIAction action, Function<bool()> conditionalFunction)
{
	this->conditionalFunction = std::move(conditionalFunction);
	this->action = action;
	this->value = "";
}

ConditionalTrigger::ConditionalTrigger(UIAction action, const String &value, Function<bool()> conditionalFunction)
{
	this->conditionalFunction = std::move(conditionalFunction);
	this->action = action;
	this->value = value;
}

bool ConditionalTrigger::Elapse()
{
	if (conditionalFunction())
	{
		Action();

		return true;
	}

	return false;
}
} // namespace WoS

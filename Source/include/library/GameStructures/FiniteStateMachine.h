#pragma once

#include <utility>

#include "Core.h"
#include "Logs.h"
#include "StringUtils.hpp"

namespace WoS
{
class FiniteStateMachine
{
public:
	using State = String;
	using Event = String;
	using Action = Function<void()>;

	struct Transition
	{
		State source;
		Event event;
		State destination;
		Action action;

		Transition() = default;

		Transition(State src, Event ev, State dest, Action act) : source(std::move(src)), event(std::move(ev)), destination(std::move(dest)), action(std::move(act)) {}

		Transition &operator=(const Transition &other)
		{
			if (this != &other)
			{
				source = other.source;
				event = other.event;
				destination = other.destination;
				action = other.action;
			}
			return *this;
		}
	};

	void AddTransition(const Transition &transition)
	{
		transitions[{transition.source, transition.event}] = Transition(transition.source, transition.event, transition.destination, transition.action);
	}

	void SetInitialState(const State &state)
	{
		currentState = state;
	}

	void TriggerEvent(const Event &event)
	{
		auto key = std::make_pair(currentState, event);

		auto it = transitions.find(key);

		if (it != transitions.end())
		{
			const auto &transition = it->second;

			if (transition.action)
			{
				transition.action();
			}

			currentState = transition.destination;

			Log::Print(StringConcat("Transitioned to state: ", currentState));
		}
		else
		{
			Log::Print(StringConcat("No transition found for state: ", currentState, " with event: ", event));
		}
	}

	State GetCurrentState() const
	{
		return currentState;
	}

private:
	struct PairHash
	{
		template <typename T1, typename T2>
		std::size_t operator()(const std::pair<T1, T2> &p) const
		{
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);
			return h1 ^ (h2 << 1);
		}
	};

	State currentState;
	HashableMap<Pair<State, Event>, Transition, PairHash> transitions;
};
} // namespace WoS

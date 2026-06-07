#pragma once

#include "Core.h"
#include "EconomyInstance.h"

namespace WoS
{
using FNPTR_ECONOMY_AWAKE = EconomyInstance *(*)(String, int);
using FNPTR_ECONOMY_START = void (*)();
using FNPTR_ECONOMY_UPDATE = void (*)(EconomyInstance *);
using FNPTR_ECONOMY_DRAW = void (*)();
using FNPTR_ECONOMY_CLEAR = void (*)();
using FNPTR_ECONOMY_DELETE = void (*)();

class Economy
{
private:
	FNPTR_ECONOMY_AWAKE awake;
	FNPTR_ECONOMY_START start;
	FNPTR_ECONOMY_UPDATE update;
	FNPTR_ECONOMY_DRAW draw;
	FNPTR_ECONOMY_CLEAR clear;
	FNPTR_ECONOMY_DELETE _delete;

	EconomyInstance *economyInstance = nullptr;

public:
	Economy(
		FNPTR_ECONOMY_AWAKE inAwake,
		FNPTR_ECONOMY_START inStart,
		FNPTR_ECONOMY_UPDATE inUpdate,
		FNPTR_ECONOMY_DRAW inDraw,
		FNPTR_ECONOMY_CLEAR inClear,
		FNPTR_ECONOMY_DELETE inDelete);

	~Economy() = default;

	void Awake(String name, int startingCash);
	void Start();
	void Update();
	void Draw();
	void Clear();
	void Delete();
};
} // namespace WoS

#pragma once

#include <SFML/Graphics.hpp>
#include "Core.h"

namespace WoS
{
using FNPTR_INTERFACE_AWAKE = void (*)(String);
using FNPTR_INTERFACE_CREATE = void (*)();
using FNPTR_INTERFACE_RENDER_WINDOW = void (*)();
using FNPTR_INTERFACE_UPDATE = void (*)();
using FNPTR_INTERFACE_CLICK = void (*)();
using FNPTR_INTERFACE_CLEAR = void (*)();
using FNPTR_INTERFACE_DELETE = void (*)();

class Interface
{
private:
	FNPTR_INTERFACE_AWAKE awake;
	FNPTR_INTERFACE_CREATE create;
	FNPTR_INTERFACE_RENDER_WINDOW draw;
	FNPTR_INTERFACE_UPDATE update;
	FNPTR_INTERFACE_CLICK click;
	FNPTR_INTERFACE_CLEAR clear;
	FNPTR_INTERFACE_DELETE _delete;

public:
	Interface(
		FNPTR_INTERFACE_AWAKE,
		FNPTR_INTERFACE_CREATE,
		FNPTR_INTERFACE_UPDATE,
		FNPTR_INTERFACE_CLICK,
		FNPTR_INTERFACE_CLEAR,
		FNPTR_INTERFACE_RENDER_WINDOW,
		FNPTR_INTERFACE_DELETE);
	~Interface() = default;

	void Awake(String name);
	void Create();
	void Draw();
	void Update();
	void Click();
	void Clear();
};
} // namespace WoS

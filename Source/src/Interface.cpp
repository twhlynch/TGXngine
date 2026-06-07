#include "Interface.h"
#include "Logs.h"

#include <utility>

namespace WoS
{
Interface::Interface(
	FNPTR_INTERFACE_AWAKE awake,
	FNPTR_INTERFACE_CREATE create,
	FNPTR_INTERFACE_UPDATE update,
	FNPTR_INTERFACE_CLICK click,
	FNPTR_INTERFACE_CLEAR clear,
	FNPTR_INTERFACE_RENDER_WINDOW draw,
	FNPTR_INTERFACE_DELETE _delete)
{
	this->awake = awake;
	this->create = create;
	this->update = update;
	this->click = click;
	this->clear = clear;
	this->draw = draw;
	this->_delete = _delete;

	Log::Success("Interface Created");
}

void Interface::Awake(String name)
{
	Log::Info("Interface::Awake");

	awake(std::move(name));
}

void Interface::Create()
{
	Log::Info("Interface::Create");

	create();
}

void Interface::Update()
{
	update();
}

void Interface::Click()
{
	click();
}

void Interface::Clear()
{
	clear();
}

void Interface::Draw()
{
	draw();
}
} // namespace WoS

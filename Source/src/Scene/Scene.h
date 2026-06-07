#pragma once

#include <SFML/Graphics.hpp>
#include "UI/Button.h"

namespace WoS
{
class Scene
{
protected:
	String name;
	Vector<Ref<Button>> buttons;

public:
	Scene()
	{
		Log::Success("Scene Created");
	}

	virtual ~Scene() = default;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Click() = 0;
	virtual void RightClick() = 0;
	virtual void Release() = 0;
	virtual void Close() = 0;
	virtual void Free() = 0;
	void SetName(const String &inName)
	{
		this->name = inName;
	}
	String GetName()
	{
		return name;
	}
};
} // namespace WoS

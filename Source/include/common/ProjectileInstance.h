#pragma once

#include <utility>

#include "Core.h"

namespace WoS
{
class ProjectileInstance
{
public:
	float damage = 0;
	int uid = 0;
	float x = 0;
	float y = 0;
	int targetUid = 0;
	float targetX = 0;
	float targetY = 0;
	int turnSpeed = 0;
	float direction = 0;
	int directions = 8;
	int spriteIndex = -1;

	virtual ~ProjectileInstance() = default;

	String GetName() const
	{
		return name;
	}

	void SetPosition(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	void SetTarget(int _uid, float _tx, float _ty)
	{
		targetUid = _uid;
		targetX = _tx;
		targetY = _ty;
	}

	virtual Unique<ProjectileInstance> Clone() const = 0;
	virtual int GetFrames() const = 0;
	virtual int GetSpeed() const = 0;
	virtual float GetDamage() const = 0;

protected:
	String name;
	ProjectileInstance(String inName) : name(std::move(inName)) {}
};
} // namespace WoS

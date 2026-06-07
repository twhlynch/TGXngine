#pragma once

#include "Core.h"

namespace WoS
{
class Instance
{
protected:
	String type;
	String name;
	String team;
	int frame = 0;
	float x = 0;
	float y = 0;
	float originX = 0.0f;
	float originY = 0.0f;
	int uid = 0;
	int width = 0;
	int height = 0;

public:
	Instance()
	{
	}

	Instance(const Instance &) = delete;
	virtual ~Instance() = default;

	Instance &operator=(const Instance &) = delete;

	int GetUid() const
	{
		return uid;
	}
	void SetUid(int inUid)
	{
		uid = inUid;
	}

	const String &GetType() const
	{
		return type;
	}
	void SetType(const String &inType)
	{
		type = inType;
	}

	const String &GetName() const
	{
		return name;
	}
	void SetName(const String &inName)
	{
		name = inName;
	}

	const String &GetTeam() const
	{
		return team;
	}
	void SetTeam(const String &inTeam)
	{
		team = inTeam;
	}

	float GetX() const
	{
		return x;
	}
	void SetX(float inX)
	{
		x = inX;
	}

	float GetY() const
	{
		return y;
	}
	void SetY(float inY)
	{
		y = inY;
	}

	float GetOriginX() const
	{
		return originX;
	}
	float GetOriginY() const
	{
		return originY;
	}

	int GetFrame() const
	{
		return frame;
	}
	void SetFrame(int inFrame)
	{
		frame = inFrame;
	}

	int GetWidth() const
	{
		return width;
	}
	void SetWidth(int inWidth)
	{
		width = inWidth;
	}

	int GetHeight() const
	{
		return height;
	}
	void SetHeight(int inHeight)
	{
		height = inHeight;
	}

	virtual int GetFrames() const = 0;
	virtual float GetRadius() const = 0;
};
} // namespace WoS

#pragma once

#include "ResourceInstance.h"

namespace TGX
{
class ResourcesStates : public ResourceInstance
{
public:
	static constexpr float radius = 2.0f;
};

class WaterState : public ResourcesStates
{
public:
	static constexpr int frames = 1;

	WaterState()
	{
	}

	int GetFrames() const override
	{
		return frames;
	}

	float GetRadius() const override
	{
		return radius;
	}
};

class OilState : public ResourcesStates
{
public:
	static constexpr int frames = 1;

	OilState()
	{
	}

	int GetFrames() const override
	{
		return frames;
	}

	float GetRadius() const override
	{
		return radius;
	}
};
} // namespace TGX

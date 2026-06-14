#pragma once

#include <utility>
#include "Core.h"

namespace TGX
{
class AssetState
{
private:
	String type;
	String name;
	float x = 0;
	float y = 0;
	float lastMovementX = 0;
	float lastMovementY = 0;
	float direction = 0;
	int speed = 0;

public:
	AssetState() = default;

	virtual ~AssetState() = default;

	String GetType() { return type; }
	void SetType(const String &newType) { type = newType; }
	void SetType(String &&newType) { type = std::move(newType); }

	String GetName() { return name; }
	void SetName(String &&newName) { name = std::move(newName); }
	void SetName(const String &newName) { name = newName; }

	float GetX() const { return x; }
	void SetX(float newX) { x = newX; }

	float GetY() const { return y; }
	void SetY(float newY) { y = newY; }

	float GetLastMovementX() const { return lastMovementX; }
	void SetLastMovementX(float newLastMovementX) { lastMovementX = newLastMovementX; }

	float GetLastMovementY() const { return lastMovementY; }
	void SetLastMovementY(float newLastMovementY) { lastMovementY = newLastMovementY; }

	float GetDirection() const { return direction; }
	void SetDirection(float newDirection) { direction = newDirection; }

	int GetSpeed() const { return speed; }
	void SetSpeed(int newSpeed) { speed = newSpeed; }

	virtual int GetFrames() const = 0;
};
} // namespace TGX

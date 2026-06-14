#pragma once

#include <cmath>
#include <numbers>
#include "Core.h"
#include "NextStep.h"
#include "WorldState.h"

namespace TGX
{
const float PI = std::numbers::pi_v<float>;

extern "C"
{
	float static GetAngleAsDegrees(const ItemInstance &item, const NextStep &nextStep)
	{
		float dx = static_cast<float>(nextStep.x) - item.GetX();
		float dy = static_cast<float>(nextStep.y) - item.GetY();

		float angleInRadians = std::atan2(dy, dx);

		float angleInDegrees = angleInRadians * (180.0f / PI);

		if (angleInDegrees < 0.0f)
		{
			angleInDegrees += 360.0f;
		}

		return angleInDegrees;
	}

	float static AngleDifference(float a, float b)
	{
		float diff = std::fabs(a - b);
		return std::fmin(diff, 360.0f - diff);
	}

	int static CoordinateToIndex(int x, int y, int width)
	{
		return (y * width) + x;
	}

	float static WrapDirection(float direction, int directions)
	{
		if (direction < 0.0f)
		{
			direction += static_cast<float>(directions);
		}
		if (direction >= static_cast<float>(directions))
		{
			direction -= static_cast<float>(directions);
		}

		return direction;
	}

	float static CalculateAngle(float direction, int directions)
	{
		return (direction / static_cast<float>(directions)) * 360.0f;
	}

	float static FindAngle(float object_x, float object_y, float unit_x, float unit_y, int directions, float offset = 0)
	{
		float dy = (object_y) - (unit_y) + offset;
		float dx = (object_x) - (unit_x) + offset;

		float angle = WrapDirection(static_cast<float>(std::round(directions / 2)) - (std::atan2(dx, dy) * static_cast<float>(directions) / (2.0f * PI)), directions);

		return angle;
	}

	float static AngleDiff(float angle1, float angle2, int directions)
	{
		if (angle1 >= static_cast<float>(directions) / 2.0f)
		{
			angle1 = angle1 - static_cast<float>(directions);
		}
		if (angle2 >= static_cast<float>(directions) / 2.0f)
		{
			angle2 = angle2 - static_cast<float>(directions);
		}

		float diff = angle2 - angle1;

		if (diff < -static_cast<float>(directions) / 2.0f)
		{
			diff += static_cast<float>(directions);
		}
		if (diff > static_cast<float>(directions) / 2.0f)
		{
			diff -= static_cast<float>(directions);
		}

		return diff;
	}

	float static DistanceBetweenTwoPoints(float startX, float startY, float endX, float endY)
	{
		float x = startX - endX;
		float y = startY - endY;

		return sqrt((x * x) + (y * y));
	}

	bool static Intersect(float x, float y, float startX, float startY, float width, float height)
	{
		return (x >= startX && x <= startX + width &&
				y >= startY && y <= startY + height);
	}

	bool static HoverFromCorner(Instance *item)
	{
		WorldState &world = WorldState::GetInstance();

		const auto itemX = (item->GetX() * 20.0f);
		const auto itemY = (item->GetY() * 20.0f);
		const auto itemWidth = static_cast<float>(item->GetWidth());
		const auto itemHeight = static_cast<float>(item->GetHeight());

		const float startX = itemX;
		const float startY = itemY + world.GetBackgroundOffsetY();

		return Intersect(world.GetGameX(), world.GetGameY(), startX, startY, itemWidth, itemHeight);
	}

	bool static HoverFromCenter(Instance *item, float radius)
	{
		WorldState &world = WorldState::GetInstance();

		const auto itemX = static_cast<float>(item->GetX() * 20.0);
		const auto itemY = static_cast<float>(item->GetY() * 20.0);
		const auto itemWidth = static_cast<float>(item->GetWidth());
		const auto itemHeight = static_cast<float>(item->GetHeight());

		const float centerX = itemX;
		const float centerY = itemY + world.GetBackgroundOffsetY();

		const float circ = radius * 2;
		const float width = itemWidth + circ;
		const float height = itemHeight + circ;

		return Intersect(world.GetGameX(), world.GetGameY(), centerX - (width / 2), centerY - (height / 2), width, height);
	}

	void static Move(int speed, int directions, ItemInstance *itemInstance)
	{
		float movement = static_cast<float>(speed) * (1.0f / 64.0f);
		float angleRadians = -(round(itemInstance->GetDirection()) / static_cast<float>(directions)) * 2.0f * PI;

		itemInstance->SetLastMovementX(-(movement * sin(angleRadians)));
		itemInstance->SetLastMovementY(-(movement * cos(angleRadians)));

		itemInstance->SetX(itemInstance->GetX() + itemInstance->GetLastMovementX());
		itemInstance->SetY(itemInstance->GetY() + itemInstance->GetLastMovementY());
	}

	bool static FindFurthestItem(ItemInstance *item, ItemInstance *collidedItem, const NextStep &nextStep, const NextStep &collidedNextStep)
	{
		float a = GetAngleAsDegrees(*item, nextStep);
		float b = GetAngleAsDegrees(*item, collidedNextStep);
		float c = GetAngleAsDegrees(*collidedItem, collidedNextStep);
		float d = GetAngleAsDegrees(*collidedItem, nextStep);

		float angleDifference1 = AngleDifference(a, b);
		float angleDifference2 = AngleDifference(c, d);

		return (angleDifference1 < angleDifference2);
	}

	int static FindLongestPath(
		int itemUid,
		int collidedItemUid,
		const Vector<std::tuple<int, int>> &itemPath,
		const Vector<std::tuple<int, int>> &collidedItemPath,
		int itemX,
		int itemY,
		int collidedItemX,
		int collidedItemY,
		int itemNextStepX,
		int itemNextStepY,
		int collidedItemNextStepX,
		int collidedItemNextStepY)
	{
		if (itemPath.size() > collidedItemPath.size())
		{
			return collidedItemUid;
		}
		if (collidedItemPath.size() > itemPath.size())
		{
			return itemUid;
		}

		float itemDistanceToNextStep = DistanceBetweenTwoPoints(static_cast<float>(itemX), static_cast<float>(itemY), static_cast<float>(itemNextStepX), static_cast<float>(itemNextStepY));
		float collidedItemDistanceToNextStep = DistanceBetweenTwoPoints(static_cast<float>(collidedItemX), static_cast<float>(collidedItemY), static_cast<float>(collidedItemNextStepX), static_cast<float>(collidedItemNextStepY));

		if (collidedItemDistanceToNextStep > itemDistanceToNextStep)
		{
			return collidedItemUid;
		}

		return itemUid;
	}
}
} // namespace TGX

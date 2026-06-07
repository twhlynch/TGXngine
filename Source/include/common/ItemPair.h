#pragma once

#include <utility>
#include "ItemInstance.h"

namespace WoS
{
struct ItemPair
{
	ItemInstance *sourceItem;
	ItemInstance *targetItem;
	String type;

	ItemPair(String _type, ItemInstance *_sourceItem, ItemInstance *_targetItem) : sourceItem(_sourceItem), targetItem(_targetItem), type(std::move(_type))
	{
	}
};
} // namespace WoS

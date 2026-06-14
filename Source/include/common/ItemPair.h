#pragma once

#include <utility>
#include "ItemInstance.h"

namespace TGX
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
} // namespace TGX

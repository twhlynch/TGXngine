#pragma once

#include "Orders.h"

namespace WoS
{
class Updater
{
public:
	static void Init()
	{
		newOrders = Orders::Order::None;
	}

	static void SetNewOrder(Orders::Order order)
	{
		updateFrame = true;
		newOrders = order;
	}

	static Orders::Order GetNewOrder()
	{
		return newOrders;
	}

	static void Reset()
	{
		if (updateFrame && newOrders != Orders::Order::None)
		{
			updateFrame = false;
			newOrders = Orders::Order::None;
		}
	}

private:
	static inline bool updateFrame = false;
	static inline Orders::Order newOrders;
};
} // namespace WoS

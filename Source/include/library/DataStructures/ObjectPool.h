#pragma once

#include "Core.h"

namespace TGX
{
template <typename T>
struct ObjectPoolNode
{
	ObjectPoolNode *next;
	T data;
};

template <typename T, size_t N>
class ObjectPool
{
public:
	ObjectPool()
	{
		for (size_t i = 0; i < N - 1; i++)
		{
			objectPool[i].next = &objectPool[i + 1];
		}

		objectPool[N - 1].next = nullptr;
		freeList = objectPool.data();
	}

	T *Borrow()
	{
		if (!freeList)
		{
			return nullptr;
		}

		ObjectPoolNode<T> *node = freeList;
		freeList = freeList->next;
		return &node->data;
	}

	void Return(T *t)
	{
		if (!t)
		{
			return;
		}

		T *base = &objectPool[0].data;
		T *end = base + N;

		if (t < base || t >= end)
		{
			return;
		}

		auto index = static_cast<size_t>(t - base);
		ObjectPoolNode<T> *node = &objectPool[index];

		node->next = freeList;
		freeList = node;
	}

private:
	Array<ObjectPoolNode<T>, N> objectPool;
	ObjectPoolNode<T> *freeList = nullptr;
};
} // namespace TGX

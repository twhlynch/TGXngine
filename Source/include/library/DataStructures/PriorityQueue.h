#pragma once

#include <algorithm>
#include "Core.h"
#include "Node/Node.h"

namespace WoS
{
template <typename T>
class PriorityQueue
{
private:
	Vector<T *> heap;

	void HeapifyUp(size_t index)
	{
		while (index > 0)
		{
			size_t parentIndex = (index - 1) / 2;
			if (heap[parentIndex]->CompareTo(*heap[index]) <= 0)
			{
				break;
			}
			std::swap(heap[parentIndex], heap[index]);
			index = parentIndex;
		}
	}

	void HeapifyDown(size_t index)
	{
		size_t leftChildIndex = (2 * index) + 1;
		size_t rightChildIndex = (2 * index) + 2;
		size_t smallest = index;

		if (leftChildIndex < heap.size() && heap[leftChildIndex]->CompareTo(*heap[smallest]) < 0)
		{
			smallest = leftChildIndex;
		}
		if (rightChildIndex < heap.size() && heap[rightChildIndex]->CompareTo(*heap[smallest]) < 0)
		{
			smallest = rightChildIndex;
		}

		if (smallest != index)
		{
			std::swap(heap[index], heap[smallest]);
			HeapifyDown(smallest);
		}
	}

public:
	void Push(T *element)
	{
		heap.push_back(element);
		HeapifyUp(heap.size() - 1);
	}

	T *Pop()
	{
		if (heap.empty())
		{
			return nullptr;
		}

		T *root = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		HeapifyDown(0);

		return root;
	}

	T *Top() const
	{
		return heap.empty() ? nullptr : heap[0];
	}

	bool Empty() const
	{
		return heap.empty();
	}

	size_t Size() const
	{
		return heap.size();
	}

	void Clear()
	{
		for (Node *node : heap)
		{
			delete node;
		}

		heap.clear();
	}
};
} // namespace WoS

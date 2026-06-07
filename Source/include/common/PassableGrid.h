#pragma once

#include <sstream>
#include "Core.h"
#include "Logs.h"
#include "StringUtils.hpp"

namespace WoS
{
class PassableGrid
{
private:
	Vector<Vector<int>> grid;
	size_t width;
	size_t height;

public:
	PassableGrid() : width(0), height(0)
	{
	}

	~PassableGrid()
	{
		Log::Print("delete Passable Grid");
	}

	void Set(size_t width, size_t height)
	{
		this->width = width;
		this->height = height;

		grid.resize(height, Vector<int>(width, 0));

		Log::Print("create Passable Grid");
	}

	int Get(int x, int y) const
	{
		x = std::clamp(x, 0, static_cast<int>(width) - 1);
		y = std::clamp(y, 0, static_cast<int>(height) - 1);
		return grid[y][x];
	}

	const Vector<Vector<int>> &GetGrid() const
	{
		return grid;
	}
	Vector<Vector<int>> &GetGrid()
	{
		return grid;
	}

	size_t GetWidth() const
	{
		return width;
	}

	size_t GetHeight() const
	{
		return height;
	}

	void Display()
	{
		for (size_t i = 0; i < this->height; i++)
		{
			for (size_t j = 0; j < this->width; j++)
			{
				grid[i][j] = 1;
			}
		}

		Log::Print(StringConcat("Height: ", this->height, " Width: ", this->width));

		for (size_t i = 0; i < this->height; i++)
		{
			std::stringstream row;
			for (size_t j = 0; j < this->width; j++)
			{
				row << grid[i][j] << " ";
			}

			Log::Print(row.str());
		}
	}
};
} // namespace WoS

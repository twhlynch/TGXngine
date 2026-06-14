#include "WavePropagation.h"

namespace TGX
{
void WavePropagation::Search(
	const Point &start,
	const Point &end,
	int cols, int rows,
	const Vector<Vector<int>> &grid,
	const Unique<ConfigurePath> & /*configure*/)
{
	if (grid[start.y][start.x] == 1)
	{
		Log::Print("Invalid End Point");
		return;
	}

	flowField.resize(rows, Vector<int>(cols, 0));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			flowField[i][j] = (grid[i][j] == 1) ? -1 : grid[i][j];
		}
	}

	Vector<Tuple<int, int, int>> nodes;

	nodes.emplace_back(end.x, end.y, 1);

	flowField[end.y][end.x] = 1;

	while (!nodes.empty())
	{
		Vector<Tuple<int, int, int>> new_nodes;

		for (auto &n : nodes)
		{
			int x = std::get<0>(n);
			int y = std::get<1>(n);
			int d = std::get<2>(n);

			if ((x + 1) < cols && flowField[y][x + 1] == 0)
			{
				new_nodes.emplace_back(x + 1, y, d + 1);
				flowField[y][x + 1] = d + 1;
			}

			if ((x - 1) >= 0 && flowField[y][x - 1] == 0)
			{
				new_nodes.emplace_back(x - 1, y, d + 1);
				flowField[y][x - 1] = d + 1;
			}

			if ((y + 1) < rows && flowField[y + 1][x] == 0)
			{
				new_nodes.emplace_back(x, y + 1, d + 1);
				flowField[y + 1][x] = d + 1;
			}

			if ((y - 1) >= 0 && flowField[y - 1][x] == 0)
			{
				new_nodes.emplace_back(x, y - 1, d + 1);
				flowField[y - 1][x] = d + 1;
			}
		}

		nodes.clear();
		nodes.insert(nodes.begin(), new_nodes.begin(), new_nodes.end());
	}

	path.push_back(start);

	int locationX = start.x;
	int locationY = start.y;
	int neighboursIndex;

	while (locationX != end.x || locationY != end.y)
	{
		Array<Tuple<int, int, int>, 4> neighbours;
		neighboursIndex = 0;

		if (locationY - 1 >= 0 && flowField[locationY - 1][locationX] > 0)
		{
			neighbours[neighboursIndex] = {locationX, locationY - 1, flowField[locationY - 1][locationX]};
			neighboursIndex++;
		}

		if (locationX + 1 < cols && flowField[locationY][locationX + 1] > 0)
		{
			neighbours[neighboursIndex] = {locationX + 1, locationY, flowField[locationY][locationX + 1]};
			neighboursIndex++;
		}

		if (locationY + 1 < rows && flowField[locationY + 1][locationX] > 0)
		{
			neighbours[neighboursIndex] = {locationX, locationY + 1, flowField[locationY + 1][locationX]};
			neighboursIndex++;
		}

		if (locationX - 1 >= 0 && flowField[locationY][locationX - 1] > 0)
		{
			neighbours[neighboursIndex] = {locationX - 1, locationY, flowField[locationY][locationX - 1]};
			neighboursIndex++;
		}

		if (neighboursIndex == 0)
		{
			Log::Print("No Path");
			break;
		}

		Tuple<int, int, int> nextStep = neighbours[0];

		for (size_t i = 0; i < static_cast<size_t>(neighboursIndex); i++)
		{
			if (std::get<2>(neighbours[i]) < std::get<2>(nextStep))
			{
				nextStep = neighbours[i];
			}
		}

		locationX = std::get<0>(nextStep);
		locationY = std::get<1>(nextStep);

		path.emplace_back(static_cast<float>(locationX), static_cast<float>(locationY));
	}
}

Vector<Point> WavePropagation::GetPath() const
{
	return path;
}

Vector<Vector<int>> WavePropagation::GetField() const
{
	return flowField;
}
} // namespace TGX

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

enum class CollisionType : uint8_t
{
	Edge = 0,
	Circle = 1,
	Rectangle = 2
};

enum class CardinalDirectionType : uint8_t
{
	North = 0,
	South = 1,
	East = 2,
	West = 3
};

struct Collision
{
	virtual void Update(float x, float y) = 0;
	virtual bool Intersect(Collision *other) = 0;
};

struct EdgeCollision : Collision
{
	float startX, startY;
	float endX, endY;

	void Update(float x, float y) override
	{
	}

	bool Intersect(Collision * /*other*/) override
	{
		return false;
	}
};

struct CircleCollision : Collision
{
	float radius;

	void Update(float x, float y) override
	{
	}

	bool Intersect(Collision *other) override
	{
		if (radius == dynamic_cast<CircleCollision *>(other)->radius)
		{
		}

		return false;
	}
};

struct RectangleCollision : Collision
{
	void Update(float x, float y) override
	{
	}

	bool Intersect(Collision * /*other*/) override
	{
		return false;
	}
};

class CollisionFactory
{
public:
	static Collision *CreateNewCollision(CollisionType type)
	{
		Collision *collision = nullptr;

		switch (type)
		{
			case CollisionType::Edge:
				collision = new EdgeCollision();
				break;
			case CollisionType::Circle:
				collision = new CircleCollision();
				break;
			case CollisionType::Rectangle:
				collision = new RectangleCollision();
				break;
			default:
				break;
		}

		return collision;
	}
};

class PolyMap
{
private:
	struct Cell
	{
		std::array<int, 4> edge_id;
		std::array<bool, 4> edge_exists;
		bool exist = false;
	};

	Cell *cells;
	std::vector<EdgeCollision> edges;

public:
	void ConvertTileMapToPolyMap(
		int /*startX*/, int /*startY*/,
		int width, int height,
		float /*tileWidth*/, int /*pitch*/)
	{
		this->cells = new Cell[static_cast<unsigned long>(width * height)];
	}
};

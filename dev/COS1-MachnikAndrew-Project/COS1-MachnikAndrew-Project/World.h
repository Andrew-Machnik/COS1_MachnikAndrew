#pragma once

#include "Tile.h"
#include <vector>

class World
{
private:
	int width;
	int height;

	std::vector<Tile> tiles;

public:
	World(int worldWidth, int worldHeight);

	void Display() const;
};
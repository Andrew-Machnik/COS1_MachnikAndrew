#pragma once

#include "Tile.h"
#include <vector>

// World Class
class World
{
private:
	int width;
	int height;

	// Store world tiles
	std::vector<Tile> tiles;

public:
	World(int worldWidth, int worldHeight);

	void Display() const;

	void Generate();

	int CountTerrain(Terrain terrain) const;

	void Resize(int worldWidth, int worldHeight);
};
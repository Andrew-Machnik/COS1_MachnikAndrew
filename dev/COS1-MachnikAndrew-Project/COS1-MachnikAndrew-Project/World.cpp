#include "World.h"
#include <iostream>
#include <random>

// Initialize world dimentions
World::World(int worldWidth, int worldHeight)
{
	width = worldWidth;
	height = worldHeight;

	tiles.resize(width * height);
}

// Display world grid
void World::Display() const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y * width + x;

			std::cout << tiles[index].GetColor()
				<< "  "
				<< "\033[0m";
		}

		std::cout << '\n';
	}
}

// Generate random terrain
void World::Generate()
{
	std::random_device rd;
	std::mt19937 generator(rd());

	std::discrete_distribution<int> distribution(
		{ 45, 30, 15, 10 }
	);

	for (Tile& tile : tiles)
	{
		switch (distribution(generator))
		{
		case 0:
			tile.SetTerrain(Terrain::Grassland);
			break;

		case 1:
			tile.SetTerrain(Terrain::Forest);
			break;

		case 2:
			tile.SetTerrain(Terrain::Water);
			break;

		case 3:
			tile.SetTerrain(Terrain::Mountain);
			break;
		}
	}
}

// Count terrain tiles
int World::CountTerrain(Terrain terrain) const
{
	int count = 0;

	for (const Tile& tile : tiles)
	{
		if (tile.GetTerrain() == terrain)
		{
			count++;
		}
	}

	return count;
}

// Resize world
void World::Resize(int worldWidth, int worldHeight)
{
	width = worldWidth;
	height = worldHeight;

	tiles.clear();
	tiles.resize(width * height);
}
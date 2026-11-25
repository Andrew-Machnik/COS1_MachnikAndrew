#include "World.h"
#include <iostream>
#include <random>

World::World(int worldWidth, int worldHeight)
{
	width = worldWidth;
	height = worldHeight;

	tiles.resize(width * height);
}

void World::Display() const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y * width + x;

			std::cout << tiles[index].GetSymbol()
				<< ' ';
		}

		std::cout << '\n';
	}
}

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
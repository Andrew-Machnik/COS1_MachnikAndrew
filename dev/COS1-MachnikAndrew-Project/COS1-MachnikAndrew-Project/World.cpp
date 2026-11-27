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

// Generate connected terrain regions
void World::Generate()
{
	std::random_device rd;
	std::mt19937 generator(rd());

	// Random region positions
	std::uniform_int_distribution<int> randomX(0, width - 1);
	std::uniform_int_distribution<int> randomY(0, height - 1);
	std::uniform_int_distribution<int> radius(1, 3);

	// Initialize Grassland
	for (Tile& tile : tiles)
	{
		tile.SetTerrain(Terrain::Grassland);
	}

	// Determin number of regions
	int regionCount = width * height / 60 + 1;
	if (regionCount < 3)
	{
		regionCount = 3;
	}

	std::discrete_distribution<int> terrainType(
		{ 50, 30, 20 }
	);

	// Generate terrain regions
	for (int i = 0; i < regionCount; i++)
	{
		int centerX = randomX(generator);
		int centerY = randomY(generator);
		int regionRadius = radius(generator);

		Terrain terrain;

		switch (i < 3 ? i : terrainType(generator))
		{
		case 0:
			terrain = Terrain::Forest;
			break;

		case 1:
			terrain = Terrain::Water;
			break;

		case 2:
			terrain = Terrain::Mountain;
			break;
		}

		// Fill surrounding area
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int dx = x - centerX;
				int dy = y - centerY;

				if (dx * dx + dy * dy <=
					regionRadius * regionRadius)
				{
					int index = y * width + x;

					// Preserve existing terrain regions
					if (tiles[index].GetTerrain() == Terrain::Grassland)
					{
						tiles[index].SetTerrain(terrain);
					}
				}
			}
		}
	}

	// Make all terrain types appear
	Terrain requiredTerrain[] =
	{
		Terrain::Grassland,
		Terrain::Forest,
		Terrain::Water,
		Terrain::Mountain
	};

	for (Terrain terrain : requiredTerrain)
	{
		if (CountTerrain(terrain) == 0)
		{
			for (Tile& tile : tiles)
			{
				if (CountTerrain(tile.GetTerrain()) > 1)
				{
					tile.SetTerrain(terrain);
					break;
				}
			}
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

// Calculate total world tiles
int World::GetTotalTiles() const
{
	return width * height;
}

// Resize world
void World::Resize(int worldWidth, int worldHeight)
{
	width = worldWidth;
	height = worldHeight;

	tiles.clear();
	tiles.resize(width * height);
}
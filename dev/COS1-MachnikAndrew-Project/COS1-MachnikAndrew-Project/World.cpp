#include "World.h"
#include <iostream>

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
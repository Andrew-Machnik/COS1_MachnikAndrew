#include "Civilization.h"
#include <cstdlib>
#include <iostream>
#include <random>


// Initialize civilization
Civilization::Civilization()
{
	Reset();
}

// Reset starting stats
void Civilization::Reset()
{
	population = 10;
	food = 50;
	wood = 20;
	stone = 10;
}

// Update civilization each turn
void Civilization::Update(const World& world)
{
	// Stop development if population = 0
	if (population == 0)
	{
		std::cout << "Your civilization has collapsed.\n";
		return;
	}

	// Count available terrain
	int grassland = world.CountTerrain(Terrain::Grassland);
	int forest = world.CountTerrain(Terrain::Forest);
	int water = world.CountTerrain(Terrain::Water);
	int mountain = world.CountTerrain(Terrain::Mountain);

	// Resource production
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<int> harvest(50, 150);

	// Population-based gathering limits
	int foodLimit = population * 2;
	int woodLimit = population / 2;
	int stoneLimit = population / 3;

	// Available resource production
	int foodProduction = grassland / 4 + water / 3;
	int woodProduction = forest / 3;
	int stoneProduction = mountain / 2;

	// Limit producion per population
	if (foodProduction > foodLimit)
		foodProduction = foodLimit;

	if (woodProduction > woodLimit)
		woodProduction = woodLimit;

	if (stoneProduction > stoneLimit)
		stoneProduction = stoneLimit;

	// Random resource production
	food += foodProduction * harvest(generator) / 100;
	wood += woodProduction * harvest(generator) / 100;
	stone += stoneProduction * harvest(generator) / 100;

	// Resource consumption
	food -= population;
	wood -= population / 3;
	stone -= population / 5;

	if (wood < 0)
		wood = 0;

	if (stone < 0)
		stone = 0;

	// Population growth/decline
	if (food < 0)
	{
		int decline = population / 10 + 1;
		population -= decline;
		food = 0;

		std::cout << "Food shortage! Population declined by "
			<< decline << ".\n";
	}
	else if (food >= population * 3)
	{
		int growth = population / 20 + 1;
		population += growth;

		std::cout << "Food surplus! Population increased by "
			<< growth << ".\n";
	}
	else
	{
		std::cout << "Population remains stable.\n";
	}
}

// Display civilization stats
void Civilization::Display() const
{
	std::cout << "\n--- Civilization ---\n";
	std::cout << "Population: " << population << '\n';
	std::cout << "Food: " << food << '\n';
	std::cout << "Wood: " << wood << '\n';
	std::cout << "Stone: " << stone << '\n';
}
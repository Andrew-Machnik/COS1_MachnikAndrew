#include "Civilization.h"
#include <cstdlib>
#include <iomanip>
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

	// Initialize previous stats
	previousPopulation = population;
	previousFood = food;
	previousWood = wood;
	previousStone = stone;

	// Reset turn events
	turnEvents.clear();
}

// Update civilization each turn
void Civilization::Update(const World& world)
{
	// Clear prior turn events
	turnEvents.clear();

	// Record previous turn stats
	previousPopulation = population;
	previousFood = food;
	previousWood = wood;
	previousStone = stone;

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

	// Calculate terrain density
	int totalTiles = world.GetTotalTiles();

	if (totalTiles <= 0)
		return;

	double grasslandDensity = static_cast<double>(grassland) / totalTiles;
	double forestDensity = static_cast<double>(forest) / totalTiles;
	double waterDensity = static_cast<double>(water) / totalTiles;
	double mountainDensity = static_cast<double>(mountain) / totalTiles;

	/* TEST(terrain density)
	std::cout << "\nTotal tiles: " << totalTiles << '\n';
	std::cout << "Grassland: " << grasslandDensity * 100 << "%\n";
	std::cout << "Forest: " << forestDensity * 100 << "%\n";
	std::cout << "Water: " << waterDensity * 100 << "%\n";
	std::cout << "Mountain: " << mountainDensity * 100 << "%\n";
	*/

	// Resource production
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<int> harvest(50, 150);

	// Population-based gathering limits
	int foodLimit = population * 2;
	int woodLimit = population / 2;
	int stoneLimit = population / 3;

	// Density-based resource production
	int foodProduction = static_cast<int>(
		population * (grasslandDensity * 2.0 + waterDensity * 3.0));
	int woodProduction = static_cast<int>(
		population * forestDensity * 4.0);
	int stoneProduction = static_cast<int>(
		population * mountainDensity * 5.0);

	// Limit producion per population
	if (foodProduction > foodLimit)
		foodProduction = foodLimit;

	if (woodProduction > woodLimit)
		woodProduction = woodLimit;

	if (stoneProduction > stoneLimit)
		stoneProduction = stoneLimit;

	// Terrain-based production limits
	int foodTerrainLimit = grassland * 2 + water * 3;
	int woodTerrainLimit = forest * 4;
	int stoneTerrainLimit = mountain * 5;

	// Random resource production
	foodProduction = foodProduction + harvest(generator) / 100;
	woodProduction = woodProduction + harvest(generator) / 100;
	stoneProduction = stoneProduction + harvest(generator) / 100;

	// Limit production per terrain
	if (foodProduction > foodTerrainLimit)
		foodProduction = foodTerrainLimit;

	if (woodProduction > woodTerrainLimit)
		woodProduction = woodTerrainLimit;

	if (stoneProduction > stoneTerrainLimit)
		stoneProduction = stoneTerrainLimit;

	// Gathered resources
	food += foodProduction;
	wood += woodProduction;
	stone += stoneProduction;

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

		turnEvents.push_back(
			"Food shortage! Population decreased by "
			+ std::to_string(decline) + ".");
	}
	else if (food >= population * 3)
	{
		int growth = population / 20 + 1;
		population += growth;

		turnEvents.push_back(
			"Food surplus! Population increased by "
			+ std::to_string(growth) + ".");
	}
	else
	{
		turnEvents.push_back("Population remains stable.");
	}

	// Resource shortage events
	if (food == 0)
	{
		turnEvents.push_back("Food reserves are depleted.");
	}

	if (wood == 0)
	{
		turnEvents.push_back("Wood reserves are depleted.");
	}

	if (stone == 0)
	{
		turnEvents.push_back("Stone reserves are depleted.");
	}
}

// Display civilization stats
void Civilization::Display() const
{
	// Calculate changes since last turn
	int populationChange = population - previousPopulation;
	int foodChange = food - previousFood;
	int woodChange = wood - previousWood;
	int stoneChange = stone - previousStone;

	std::cout << "\n--- CIVILIZATION ---\n";
	
	std::cout << std::left << std::setw(15)
		<< "Population:" << population
		<< " (" << std::showpos << populationChange
		<< std::noshowpos << ")\n";

	std::cout << std::left << std::setw(15)
		<< "Food:" << food
		<< " (" << std::showpos << foodChange
		<< std::noshowpos << ")\n";

	std::cout << std::left << std::setw(15)
		<< "Wood:" << wood
		<< " (" << std::showpos << woodChange
		<< std::noshowpos << ")\n";

	std::cout << std::left << std::setw(15)
		<< "Stone:" << stone
		<< " (" << std::showpos << stoneChange
		<< std::noshowpos << ")\n";

	std::cout << std::right;
}

// Display turn events
void Civilization::DisplayEvents() const
{
	std::cout << "\n--- TURN EVENTS ---\n";

	if (turnEvents.empty())
	{
		std::cout << "No events this turn.\n";
		return;
	}

	for (const std::string& event : turnEvents)
	{
		std::cout << "- " << event << '\n';
	}
}
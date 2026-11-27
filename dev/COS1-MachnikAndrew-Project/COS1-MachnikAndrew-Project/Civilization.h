#pragma once
#include "World.h"
#include <string>
#include <vector>

// Civilization Class
class Civilization
{
private:
	// Civilization statistics
	int population;
	int food;
	int wood;
	int stone;
	
	// Previous turn
	int previousPopulation;
	int previousFood;
	int previousWood;
	int previousStone;

	// Turn events
std::vector<std::string> turnEvents;

public:
	Civilization();

	void Reset();
	void Update(const World& world);
	void Display() const;

	void DisplayEvents() const;
};
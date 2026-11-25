#pragma once
#include "World.h"

// Civilization Class
class Civilization
{
private:
	// Civilization statistics
	int population;
	int food;
	int wood;
	int stone;

public:
	Civilization();

	void Reset();
	void Update(const World& world);
	void Display() const;
};
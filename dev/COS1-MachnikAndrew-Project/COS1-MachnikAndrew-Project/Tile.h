#pragma once
#include <string>

// Terrain types
enum class Terrain
{
	Grassland,
	Forest,
	Water,
	Mountain
};

// Tile Class
class Tile
{
private:
	Terrain terrain;

public:
	Tile();

	Terrain GetTerrain() const;
	void SetTerrain(Terrain newTerrain);

	std::string GetSymbol() const;
};
#pragma once

enum class Terrain
{
	Grassland,
	Forest,
	Water,
	Mountain
};

class Tile
{
private:
	Terrain terrain;

public:
	Tile();

	Terrain GetTerrain() const;
	void SetTerrain(Terrain newTerrain);

	char GetSymbol() const;
};
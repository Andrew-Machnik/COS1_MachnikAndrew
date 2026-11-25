#include "Tile.h"
#include <string>

// Initialize terrain tile
Tile::Tile()
{
	terrain = Terrain::Grassland;
}

// Return terrain type
Terrain Tile::GetTerrain() const
{
	return terrain;
}

void Tile::SetTerrain(Terrain newTerrain)
{
	terrain = newTerrain;
}

std::string Tile::GetSymbol() const
{
	switch (terrain)
	{
	case Terrain::Grassland:
		return "__";

	case Terrain::Forest:
		return "||";

	case Terrain::Water:
		return "~~";

	case Terrain::Mountain:
		return "^^";

	default:
		return "??";
	}
}
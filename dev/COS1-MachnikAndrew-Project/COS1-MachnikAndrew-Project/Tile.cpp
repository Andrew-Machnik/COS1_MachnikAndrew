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

// Terrain background color
std::string Tile::GetColor() const
{
	switch (terrain)
	{
	case Terrain::Grassland:
		return "\033[48;2;106;168;79m";

	case Terrain::Forest:
		return "\033[48;2;101;67;33m";

	case Terrain::Water:
		return "\033[48;2;40;110;190m";

	case Terrain::Mountain:
		return "\033[48;2;140;140;140m";

	default:
		return "\033[48;2;0;0;0m";
	}
}
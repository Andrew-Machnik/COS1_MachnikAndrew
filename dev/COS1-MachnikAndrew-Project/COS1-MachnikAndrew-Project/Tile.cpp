#include "Tile.h"

Tile::Tile()
{
	terrain = Terrain::Grassland;
}

Terrain Tile::GetTerrain() const
{
	return terrain;
}

void Tile::SetTerrain(Terrain newTerrain)
{
	terrain = newTerrain;
}

char Tile::GetSymbol() const
{
	switch (terrain)
	{
	case Terrain::Grassland:
		return '.';

	case Terrain::Forest:
		return 'F';

	case Terrain::Water:
		return '~';

	case Terrain::Mountain:
		return 'M';

	default:
		return '?';
	}
}
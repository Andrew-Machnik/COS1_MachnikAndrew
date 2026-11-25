#include "World.h"
#include <iostream>

int main()
{
	World world(12, 8);

	world.Generate();
	
	world.Display();

	return 0;
}

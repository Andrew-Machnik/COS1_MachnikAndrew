#include "World.h"
#include <iostream>

int main()
{
	World world(12, 8);

	std::cout << "========================\n";
	std::cout << "         WORLD\n";
	std::cout << "========================\n\n";

	world.Display();

	return 0;
}

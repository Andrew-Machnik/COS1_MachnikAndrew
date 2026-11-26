#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>

// Initialize game settings
Game::Game()
	: world(12, 8),
	state(GameState::MainMenu),
	turn(1)
{
}

// Main game loop
void Game::Run()
{
	while (state != GameState::Exit)
	{
		switch (state)
		{
		case GameState::MainMenu:
			ShowMainMenu();
			break;

		case GameState::Playing:
			ShowGameMenu();
			break;

		case GameState::Exit:
			break;
		}
	}

	std::cout << "\nThanks for playing!\n";
}

// Display main menu
void Game::ShowMainMenu()
{
	std::cout << "\n============================\n";
	std::cout << "   CIVILIZATION SIMULATOR\n";
	std::cout << "============================\n";

	std::cout << "1. New Game\n";
	std::cout << "0. Exit\n";

	int choice = GetMenuChoice(0, 1);

	switch (choice)
	{
	case 1:
		StartNewGame();
		break;

	case 0:
		state = GameState::Exit;
		break;
	}
}

// Select world size | generate world | reset game data
void Game::StartNewGame()
{
	std::cout << "\n==============================\n";
	std::cout << "       SELECT WORLD SIZE\n";
	std::cout << "==============================\n";

	std::cout << "1. Small (12 x 8)\n";
	std::cout << "2. Medium (24 x 16)\n";
	std::cout << "3. Large (36 x 24)\n";
	std::cout << "4. Massive (48 x 32)\n";
	std::cout << "0. Return to Main Menu\n";

	int choice = GetMenuChoice(0, 4);

	switch (choice)
	{
	case 1:
		world.Resize(12, 8);
		break;

	case 2:
		world.Resize(24, 16);
		break;

	case 3:
		world.Resize(36, 24);
		break;

	case 4:
		world.Resize(48, 32);
		break;

	default:
		return;
	}

	world.Generate();
	civilization.Reset();

	turn = 1;
	state = GameState::Playing;

	std::cout << "\nA new world has been created.\n";
}

// Display world | stats | player options
void Game::ShowGameMenu()
{
	std::cout << "\n============================\n";
	std::cout << "Turn: " << turn << '\n';
	std::cout << "============================\n";

	world.Display();
	civilization.Display();

	std::cout << "\n1. Advance Turn\n";
	std::cout << "0. Return to Main Menu\n";

	int choice = GetMenuChoice(0, 1);

	switch (choice)
	{
	case 1:
		AdvanceTurn();
		break;

	case 0:
		state = GameState::MainMenu;
		break;
	}
}

// Advance time | update civilization
void Game::AdvanceTurn()
{
	++turn;
	civilization.Update(world);

	std::cout << "\nTime has advanced.\n";
}

// Validate player input
int Game::GetMenuChoice(int minimum, int maximum)
{
	std::string input;
	int choice;
	char extra;

	while (true)
	{
		std::cout << "\nEnter your choice: ";

		if (!std::getline(std::cin, input))
		{
			state = GameState::Exit;
			return -1;
		}

		std::istringstream stream(input);

		// Check input | validate range
		if (stream >> choice &&
			!(stream >> extra) &&
			choice >= minimum &&
			choice <= maximum)
		{
			return choice;
		}

		std::cout << "Invalid selection. Try again.\n";
	}
}
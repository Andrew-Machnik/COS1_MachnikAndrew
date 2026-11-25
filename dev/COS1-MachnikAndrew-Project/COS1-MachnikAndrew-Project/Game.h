#pragma once

#include "World.h"
#include "Civilization.h"

// Available game states
enum class GameState
{
	MainMenu,
	Playing,
	Exit
};

// Game Class
class Game
{
// Game functions
private:
	World world;
	Civilization civilization;
	GameState state;
	int turn;

	void ShowMainMenu();
	void ShowGameMenu();
	void StartNewGame();
	void AdvanceTurn();

	int GetMenuChoice(int minimum, int maximum);

public:
	Game();

	void Run();
};
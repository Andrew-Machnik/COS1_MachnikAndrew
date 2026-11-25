#pragma once

#include "World.h"

enum class GameState
{
	MainMenu,
	Playing,
	Exit
};

class Game
{
private:
	World world;
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
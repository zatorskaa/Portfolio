#include "GameEngine.h"

void main()
{
	//create game engine
	GameEngine* gameEngine = new GameEngine();
	bool running = true;

	while (running)
	{
		//update game engine while Update() returns true
		running = gameEngine->Update();
	}

	//delete game engine pointer
	delete gameEngine;
}
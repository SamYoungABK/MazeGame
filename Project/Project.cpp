#include <iostream>
#include "vld.h"
#include "Game.h"
#include "AudioManager.h"
#include "CustomLevelManager.h"
#include "StateMachineExampleGame.h"

using namespace std;

int main()
{
	Game myGame;

	StateMachineExampleGame gameStateMachine(&myGame);

	myGame.Initialize(&gameStateMachine);

	myGame.RunGameLoop();

	myGame.Deinitialize();

	AudioManager::DestroyInstance();
	CustomLevelManager::DestroyInstance();
	return 0;
}
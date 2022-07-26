#include "LevelSelectState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kLevelSelect = '4';
constexpr char kQuit = '5';

LevelSelectState::LevelSelectState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void LevelSelectState::Enter() {
	/*GetLevelList();*/
}

bool LevelSelectState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
		else if ((char)input == kHighScore)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::HighScore);
		}
		else if ((char)input == kLevelSelect)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::LevelSelect);
		}
		else if ((char)input == kSettings)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
	}
	return shouldQuit;
}

void LevelSelectState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - LEVEL SELECT - - -" << endl << endl;
}
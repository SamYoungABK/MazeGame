#include "LevelSelectState.h"

#include <iostream>
#include <conio.h>

#include "CustomLevelManager.h"

#include "StateMachineExampleGame.h"


using namespace std;
using std::string;
using std::vector;

constexpr int kEscapeKey = 27;
constexpr int kEnterKey = 13;

LevelSelectState::LevelSelectState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void LevelSelectState::Enter() {
	CustomLevelManager::GetInstance()->BuildLevelList();
}

bool LevelSelectState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey)
		{
			shouldQuit = true;
		}
		else if ((char)input == 'w' || (char)input == 'W')
		{
			CustomLevelManager::GetInstance()->MoveCursorUp();
		}
		else if ((char)input == 's' || (char)input == 'S')
		{
			CustomLevelManager::GetInstance()->MoveCursorDown();
		}
		else if ((char)input == kEnterKey)
		{
			CustomLevelManager::GetInstance()->m_loadCustomLevel = true;
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
	}
	return shouldQuit;
}

void LevelSelectState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - LEVEL SELECT - - -" << endl << endl;
	cout << "        Controls:" << endl;
	cout << "        W/S   - Move Cursor Up/Down" << endl;
	cout << "        ENTER - Select Level" << endl << endl;
	CustomLevelManager::GetInstance()->DrawLevelList();
		
}


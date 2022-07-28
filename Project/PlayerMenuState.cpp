#include "PlayerMenuState.h"

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "CustomLevelManager.h"
#include "SelectionMenu.h"
#include "StateMachineExampleGame.h"
#include "Player.h"


using namespace std;
using std::string;
using std::vector;

constexpr int kEscapeKey = 27;
constexpr int kEnterKey = 13;

PlayerMenuState::PlayerMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_pPlayer = m_pOwner->m_savedPlayerPtr;
}

void PlayerMenuState::Enter() {
	CustomLevelManager::GetInstance()->BuildLevelList();
}

bool PlayerMenuState::Update(bool processInput)
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
			m_selectionMenu->MoveCursorUp();
		}
		else if ((char)input == 's' || (char)input == 'S')
		{
			m_selectionMenu->MoveCursorDown();
		}
		else if ((char)input == 'x' || (char)input == 'X')
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::ResumeSaved);
		}
	}
	return shouldQuit;
}

void PlayerMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - PLAYER MENU - - -" << endl << endl;
	cout << "      Controls:" << endl;
	cout << "          W/S - Move Cursor Up/Down" << endl;
	cout << "        ENTER - Select" << endl;
	cout << "            X - Return to Game" << endl;
	cout << "            (WIP! Options don't work yet)" << endl << endl;
	PrintMoneyAndHealth();
	m_selectionMenu->PrintOptions();

}

void PlayerMenuState::PrintMoneyAndHealth()
{
	cout << "             $: " <<
		m_pPlayer->m_money <<
		"    HP: " << m_pPlayer->m_health << '/'
		<< m_pPlayer->m_vitality << endl << endl;
}


#include "PlayerMenuState.h"

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>

#include "CustomLevelManager.h"
#include "SelectionMenu.h"
#include "StateMachineExampleGame.h"
#include "Player.h"
#include "Level.h"
#include "Item.h"


using namespace std;
using std::string;
using std::vector;

constexpr int kEscapeKey = 27;
constexpr int kEnterKey = 13;

PlayerMenuState::PlayerMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_pPlayer = m_pOwner->m_savedPlayerPtr;
	m_selectedItem = m_pPlayer->m_inventory.begin();
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
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::ResumeSaved);
		}
		else if ((char)input == 'w' || (char)input == 'W')
		{
			MoveCursorUp();
		}
		else if ((char)input == 's' || (char)input == 'S')
		{
			MoveCursorDown();
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
	cout << "         - - - PAUSE MENU - - -" << endl << endl;
	cout << "      Controls:" << endl;
	cout << "          W/S - Move Cursor Up/Down" << endl;
	cout << "        ENTER - Select" << endl;
	cout << "            X - Return to Game" << endl << endl;
	PrintMoneyAndHealth();
	PrintStats(3, 12);
	PrintEquipment(20, 12);
	PrintItemList(60,3);
	/*m_selectionMenu->PrintOptions();*/

}

void PlayerMenuState::MoveConsoleCursor(int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(console, pos);
}

void PlayerMenuState::PrintMoneyAndHealth()
{
	cout << "             $: " <<
		m_pPlayer->m_money <<
		"    HP: " << m_pPlayer->m_health << '/'
		<< m_pPlayer->m_vitality << endl << endl;
}

void PlayerMenuState::PrintStats(int x, int y)
{
	MoveConsoleCursor(x, y);
	cout << "Strength : " << m_pPlayer->m_strength;
	MoveConsoleCursor(x, y + 1);
	cout << "Defense : " << m_pPlayer->m_defense;
	MoveConsoleCursor(x, y + 2);
	cout << "Dexterity: " << m_pPlayer->m_dexterity;
	MoveConsoleCursor(x, y + 3);
	cout << "Vitality : " << m_pPlayer->m_vitality;
}

void PlayerMenuState::PrintEquipment(int x, int y)
{
	MoveConsoleCursor(x, y);
	cout << "Head: " << "WIP";
	MoveConsoleCursor(x, y + 1);
	cout << "Chest: " << "WIP";
	MoveConsoleCursor(x, y + 2);
	cout << "Legs: " << "WIP";
	MoveConsoleCursor(x, y + 3);
	cout << "Weapon: " << "WIP";
}

void PlayerMenuState::PrintItemList(int x, int y)
{
	MoveConsoleCursor(x, y);
	for (int i = -1; i <= 25; ++i) cout << Level::WAL;
	MoveConsoleCursor(x, ++y);
	cout << Level::WAL << "Inventory";
	MoveConsoleCursor(x+26, y);
	cout << Level::WAL;
	MoveConsoleCursor(x, ++y);
	for (int i = -1; i <= 25; ++i) cout << Level::WAL;
	for (Item &item : m_pPlayer->m_inventory)
	{
		MoveConsoleCursor(x, ++y);
		cout << Level::WAL << ShowSelectionChar(item) << item.GetName();
		MoveConsoleCursor(x + 26, y);
		cout << Level::WAL;
	}
	MoveConsoleCursor(x, ++y);
	for (int i = -1; i <= 25; ++i) cout << Level::WAL;
}

std::string PlayerMenuState::ShowSelectionChar(Item &item)
{
	if (m_selectedItem._Ptr == &item) return " * ";
	return "   ";
}

void PlayerMenuState::MoveCursorDown()
{
	if (m_selectedItem+1 < m_pPlayer->m_inventory.end()) m_selectedItem++;
}

void PlayerMenuState::MoveCursorUp()
{
	if (m_selectedItem > m_pPlayer->m_inventory.begin()) m_selectedItem--;
}
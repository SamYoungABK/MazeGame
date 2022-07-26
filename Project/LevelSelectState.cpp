#include "LevelSelectState.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <iterator>

#include "StateMachineExampleGame.h"


using namespace std;
using std::experimental::filesystem::directory_iterator;
using std::string;
using std::vector;

constexpr int kEscapeKey = 27;
constexpr int kEnterKey = 13;

constexpr char kUpArrow = 'w';
constexpr char kDownArrow = 's';

LevelSelectState::LevelSelectState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void LevelSelectState::Enter() {
	GetLevelList();
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
		else if ((char)input == kUpArrow)
		{
			MoveCursorUp();
		}
		else if ((char)input == kDownArrow)
		{
			MoveCursorDown();
		}
		else if ((char)input == kEnterKey)
		{

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
	for (const auto& levelName : *m_levelList)
	{
		cout << "           " << IsLevelSelected(levelName) << " " << levelName << endl;
	}
		
}

void LevelSelectState::GetLevelList()
{
	string p = "../CustomLevels/";
	vector<string> result;

	delete m_levelList;
	m_levelList = new std::vector<std::string>;
	

	for (const auto& entry : directory_iterator(p))
	{
		string filename = entry.path().filename().string();
		m_levelList->push_back(filename);
	}
	m_selectedLevel = m_levelList->begin();
}

char LevelSelectState::IsLevelSelected(string levelName)
{
	if (*m_selectedLevel == levelName)
		return '*';
	else
		return ' ';
}

void LevelSelectState::MoveCursorUp()
{
	if (m_selectedLevel == m_levelList->begin()) return;

	m_selectedLevel--;
}

void LevelSelectState::MoveCursorDown()
{
	if (m_selectedLevel+1 == m_levelList->end()) return;

	m_selectedLevel++;
}

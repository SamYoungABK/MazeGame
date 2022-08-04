#include <windows.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "HealthPickup.h"

using namespace std;

Level::Level()
	: m_pLevelData(nullptr)
	, m_height(0)
	, m_width(0)
{

}

Level::~Level()
{
	if (m_pLevelData != nullptr)
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}
}

bool Level::Load(std::string levelName, int* playerX, int* playerY)
{
	levelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile)
	{
		cout << "Opening file failed: " << levelName << endl;
		return false;
	}
	else
	{
		constexpr int tempSize = 25;
		char temp[tempSize];

		// Read width
		levelFile.getline(temp, tempSize, '\n');
		m_width = atoi(temp);

		// Read height 
		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);

		// Read level
		m_pLevelData = new char[m_width * m_height];
		levelFile.read(m_pLevelData, (long long)m_width * (long long)m_height);
		
		// Convert level
		bool anyWarnings = ConvertLevel(playerX, playerY);
		if (anyWarnings)
		{
			cout << "There were some warnings in the level data, see above." << endl;
			system("pause");
		}
		return true;
	}
}
void Level::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);

	// Draw the Level
	for (int y = 0; y < GetHeight(); ++y)
	{
		for (int x = 0; x < GetWidth(); ++x)
		{
			int indexToPrint = GetIndexFromCoordinates(x, y);
			cout << m_pLevelData[indexToPrint];
		}
		cout << endl;
	}

	COORD actorCursorPosition;

	// Draw actors
	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		if ((*actor)->IsActive())
		{
			actorCursorPosition.X = (*actor)->GetXPosition();
			actorCursorPosition.Y = (*actor)->GetYPosition();
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}
}

bool Level::IsSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}
bool Level::IsWall(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == WAL;
}

bool Level::ConvertLevel(int* playerX, int* playerY)
{
	bool anyWarnings = false;
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			int index = GetIndexFromCoordinates(x, y);
			switch (m_pLevelData[index])
			{
			case '+':
			case '|':
			case '-':
				m_pLevelData[index] = WAL;
				break;
			// health pickup
			case 'a':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new HealthPickup(x, y, 1 + rand() % 5));
				break;
			case 'r':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Red));
				break;
			case 'g':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Green));
				break;
			case 'b':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Blue));
				break;
			case 'R':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidRed));
				break;
			case 'G':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Green, ActorColor::SolidGreen));
				break;
			case 'B':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Blue, ActorColor::SolidBlue));
				break;
			case 'X':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Goal(x, y));
				break;
			case '$':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr)
				{
					*playerX = x;
					*playerY = y;
				}
				break;
			case 'e':
				m_pActors.push_back(new Enemy(x, y));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'h':
				m_pActors.push_back(new Enemy(x, y, 3, 0));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'v':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Enemy(x, y, 0, 2));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}

	return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
	return x + y * m_width;
}

// Updates all actors and returns a list of pairs of colliding actors
vector<pair<PlacableActor*, PlacableActor*>> Level::UpdateActors(int x, int y, Player* player)
{
	vector<pair<PlacableActor*, PlacableActor*>> collisionList;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor) (*actor)->Update();

	char tileMovedOn = m_pLevelData[GetIndexFromCoordinates(x, y)];

	if (tileMovedOn == WAL) player->SkipNextPositionUpdate();

	// the player isnt in the list of actors in the level for some reason??? so we do this
	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		if (!(*actor)->IsActive()) continue;
		if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition())
		{
			collisionList.push_back(pair<PlacableActor*, PlacableActor*>(player, *actor));
		}
	}

	for (auto actor1 = m_pActors.begin(); actor1 != m_pActors.end(); ++actor1)
	{
		for (auto actor2 = m_pActors.begin(); actor2 != m_pActors.end(); ++actor2)
		{
			if (actor1 == actor2) continue;
			if (!((*actor1)->IsActive() && (*actor2)->IsActive())) continue;

			if ((*actor1)->GetXPosition() == (*actor2)->GetXPosition() &&
				(*actor1)->GetYPosition() == (*actor2)->GetYPosition())
			{
				collisionList.push_back(pair<PlacableActor*, PlacableActor*>(*actor1,*actor2));
			}
		}
	}

	return collisionList;
}

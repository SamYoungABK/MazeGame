#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <vector>
#include <string>
#include <thread>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"
#include "CustomLevelManager.h"
#include "HealthPickup.h"
#include "Item.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

void GameplayState::OpenPlayerMenu()
{
	m_pOwner->m_savedPlayerPtr = &m_player;
	m_pOwner->LoadScene(StateMachineExampleGame::SceneName::PlayerMenu);
}

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
	, m_beatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
	, m_inputThread(nullptr)
{
	if (CustomLevelManager::GetInstance()->m_loadCustomLevel == true)
	{
		m_LevelNames.push_back("CustomLevels/" + *(CustomLevelManager::GetInstance()->m_selectedLevel));
	}
	else {
		m_LevelNames.push_back("Level1.txt");
		m_LevelNames.push_back("Level2.txt");
		m_LevelNames.push_back("Level3.txt");
	}
}

GameplayState::~GameplayState()
{
	CustomLevelManager::GetInstance()->m_loadCustomLevel = false;
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();

	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());

}

void GameplayState::Enter()
{
	// check if we're resuming from a previously existing state
	if (m_pOwner->m_resumingSavedState)
	{
		m_pOwner->m_resumingSavedState = false;
		return;
	}
	Load();
}

void GameplayState::HandleLevelComplete()
{
	++m_skipFrameCount;
	if (m_skipFrameCount > kFramesToSkip)
	{
		m_beatLevel = false;
		m_skipFrameCount = 0;
		++m_currentLevel;
		if (m_currentLevel == m_LevelNames.size())
		{
			Utility::WriteHighScore(m_player.GetMoney());

			AudioManager::GetInstance()->PlayWinSound();

			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
		}
		else
		{
			// On to the next level
			Load();
		}

	}
}

void GameplayState::HandleLoss()
{
	m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
}

bool GameplayState::HandleInput(int& newPlayerX, int& newPlayerY)
{
	if (m_inputThread == nullptr)
	{
		m_inputThread = new std::thread(&GameplayState::getInput, this);
	}
	int input = m_input;
	int arrowInput = 0;

	// One of the arrow keys were pressed
	if (input == kArrowInput)
	{
		//arrowInput = _getch();
	}

	if ((input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}
	else if ((input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}
	else if ((char)input == 'X' || (char)input == 'x')
	{
		OpenPlayerMenu();
	}
	else if (input == kEscapeKey)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}

	return !(newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition());
}

bool GameplayState::Update(bool processInput)
{
	if (m_beatLevel) HandleLevelComplete();

	if (processInput)
	{
		int newPlayerX = m_player.GetXPosition();
		int newPlayerY = m_player.GetYPosition();

		HandleInput(newPlayerX, newPlayerY);
		HandleCollision(newPlayerX, newPlayerY);
		m_player.SetPosition(newPlayerX, newPlayerY);
	}

	if (ShouldPlayerLose()) HandleLoss();


	return false;
}

bool GameplayState::ShouldPlayerLose()
{
	return m_player.GetHealth() < 0;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	/*typedef std::pair<PlacableActor*, PlacableActor*> CollisionPair;*/
	std::vector<CollisionPair> collisionList = m_pLevel->UpdateActors(newPlayerX, newPlayerY, &m_player);

	for (CollisionPair collision : collisionList)
	{
		if (collision.first->GetType() == ActorType::Player && collision.second->GetType() == ActorType::Goal)
			m_beatLevel = true;
		collision.first->HandleCollision(collision.second);
		collision.second->HandleCollision(collision.first);
	}
}
void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL
		<< " x-open menu " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;
	cout << " hp:" << m_player.GetHealth() << "/" << m_player.GetTotalVitality();

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	
	SetConsoleCursorPosition(console, pos);
	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
	DrawHUDBroadcasts(console, csbi);
}

void GameplayState::DrawHUDBroadcasts(const HANDLE& console, CONSOLE_SCREEN_BUFFER_INFO csbi)
{
	COORD pos;
	pos.X = m_pLevel->GetWidth();
	pos.Y = m_pLevel->GetHeight() - m_broadcastMessages.size();
	SetConsoleCursorPosition(console, pos);

	for (std::string msg : m_broadcastMessages)
	{
		cout << ' ' << msg;
		pos.Y++;
		SetConsoleCursorPosition(console, pos);
	}
	cout << endl;
}

void GameplayState::BroadcastMessage(std::string message)
{
	m_broadcastMessages.push_back(message);
}
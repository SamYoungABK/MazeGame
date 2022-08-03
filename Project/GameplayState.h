#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	bool m_loadCustomLevel = false;

	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;
	std::vector<std::string> m_broadcastMessages;

public:
	void OpenPlayerMenu();
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();
	void HandleLevelComplete();
	bool HandleInput(int& newPlayerX, int& newPlayerY);
	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
	void DrawHUDBroadcasts(const HANDLE& console, CONSOLE_SCREEN_BUFFER_INFO csbi);
	void BroadcastMessage(std::string message);
	bool ShouldPlayerLose();
	void HandleLoss();
};

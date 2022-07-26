#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include <iterator>

class StateMachineExampleGame;

class LevelSelectState : public GameState
{
	StateMachineExampleGame* m_pOwner;
private:
	std::vector<std::string> *m_levelList = new std::vector<std::string>();
	std::vector<std::string>::iterator m_selectedLevel;
	
public:
	
	LevelSelectState(StateMachineExampleGame* pOwner);
	~LevelSelectState() = default;

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	void GetLevelList();
	char IsLevelSelected(std::string levelName);
	void MoveCursorUp();
	void MoveCursorDown();

};


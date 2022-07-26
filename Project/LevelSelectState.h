#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class LevelSelectState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	LevelSelectState(StateMachineExampleGame* pOwner);
	~LevelSelectState() = default;

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};


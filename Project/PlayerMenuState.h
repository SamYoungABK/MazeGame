#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include <iterator>
#include "SelectionMenu.h"
#include "Player.h"
#include "PlayerDataManager.h"

class StateMachineExampleGame;

class PlayerMenuState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	Player* m_pPlayer = nullptr;

	SelectionMenu *m_selectionMenu = new SelectionMenu({ "Stats", "Items", "Equipment"});

public:
	PlayerMenuState(StateMachineExampleGame* pOwner);
	~PlayerMenuState() = default;

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	void PrintMoneyAndHealth();
	int GetManagerValue(PlayerStats valName);
};


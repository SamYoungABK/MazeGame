#pragma once
#include "GameState.h"
#include <vector>
#include <string>
#include <iterator>
#include "SelectionMenu.h"
#include "Player.h"
#include "Item.h"

class StateMachineExampleGame;

class PlayerMenuState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	Player* m_pPlayer;
	std::vector<Item>::iterator m_selectedItem;
	std::string m_message = "";

	SelectionMenu *m_selectionMenu = new SelectionMenu({"Items"});

public:
	PlayerMenuState(StateMachineExampleGame* pOwner);
	~PlayerMenuState() {
		delete m_selectionMenu;
	};

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	
	// these should probably be their own class
	void MoveConsoleCursor(int x, int y);
	void PrintMoneyAndHealth();
	void PrintStats(int x, int y);
	void PrintEquipment(int x, int y);
	void PrintItemList(int x, int y);
	void PrintMessage(int x, int y);

	std::string ShowSelectionChar(Item &item);
	void MoveCursorDown();
	void MoveCursorUp();
	void EquipItem();
	void UseConsumable();

};


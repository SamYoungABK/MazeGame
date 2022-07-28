#pragma once
#include <string>
#include "ItemData.h"

class Item
{
	std::string m_itemName = "";
	ItemType m_itemType = ItemType::UndefinedType;
	ItemSlot m_itemSlot = ItemSlot::UndefinedSlot;
	s_StatChange m_statChange;
	int quantity = 0;

public:
	Item(int itemID) :
		m_itemName(itemInfo[itemID].itemName),
		m_itemType(itemInfo[itemID].itemType),
		m_itemSlot(itemInfo[itemID].itemSlot),
		m_statChange(itemInfo[itemID].statChange) {};

	std::string GetName() { return m_itemName; }
	ItemType GetType() { return m_itemType; }
	ItemSlot GetSlot() { return m_itemSlot; }
	int GetStrength() { return m_statChange.strength;  }
	int GetDefense() { return m_statChange.defense; }
	int GetDexterity() { return m_statChange.dexterity; }
	int GetVitality() { return m_statChange.vitality; }
};


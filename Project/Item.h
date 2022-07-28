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
	bool IsItemEquippable(ItemSlot slot)
	{
		if (m_itemType != ItemType::Equipment) return false;
		if (m_itemSlot != slot) return false;
		
		return true;
	}
	/*bool operator==(Item rhs);*/
};


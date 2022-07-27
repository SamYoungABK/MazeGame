#pragma once
#include <string>

enum class ItemType {
	Undefined,
	Key,
	Consumable,
	Equipment
};


class Item
{
	std::string m_itemName = "";
	ItemType m_itemType = ItemType::Undefined;

};


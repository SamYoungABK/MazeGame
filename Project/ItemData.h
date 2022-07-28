#pragma once
#include <string>

enum class ItemType {
	UndefinedType,
	Consumable,
	Equipment
};

enum class ItemSlot {
	UndefinedSlot,
	Head,
	Chest,
	Legs,
	Weapon
};
struct s_StatChange
{
	int strength;
	int defense;
	int dexterity;
	int vitality;
};

struct s_ItemData
{
	int itemID;
	std::string itemName;
	ItemType itemType;
	ItemSlot itemSlot;
	s_StatChange statChange;
};

const s_ItemData itemInfo[2] =
{
	{
		0, // item ID
		"Health Potion", // itemName
		ItemType::Consumable, // itemType
		ItemSlot::UndefinedSlot, //itemSlot
		{ //statChange
			0, //strength
			0, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		1, // item ID
		"Bronze Sword", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Weapon, //itemSlot
		{ //statChange
			2, //strength
			0, //defense
			0, //dexterity
			0 //vitality
		}
	},
};
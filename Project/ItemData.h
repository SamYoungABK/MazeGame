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

const s_ItemData itemInfo[10] =
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
			3, //strength
			0, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		2, // item ID
		"Leather Cowl", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Head, //itemSlot
		{ //statChange
			0, //strength
			1, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		3, // item ID
		"Leather Body", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Head, //itemSlot
		{ //statChange
			0, //strength
			1, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		4, // item ID
		"Leather Chaps", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Head, //itemSlot
		{ //statChange
			0, //strength
			1, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		5, // item ID
		"Wooden Stick", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Weapon, //itemSlot
		{ //statChange
			1, //strength
			0, //defense
			0, //dexterity
			0 //vitality
		}
	},
	{
		6, // item ID
		"Crown of Health", // itemName
		ItemType::Equipment, // itemType
		ItemSlot::Head, //itemSlot
		{ //statChange
			0, //strength
			0, //defense
			0, //dexterity
			10 //vitality
		}
	}
};
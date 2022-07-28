#pragma once
#include "PlacableActor.h"
#include <vector>
#include "Item.h"

class Key;

class Player : public PlacableActor
{
public:
	int m_money = 0;
	int m_health = 10;
	int m_strength = 2;
	int m_defense = 0;
	int m_dexterity = 1;
	int m_vitality = 10;
	std::vector<Item> m_inventory = { Item(0), Item(1) };

	Item m_headEquipped   = -1;
	Item m_chestEquipped  = -1;
	Item m_legsEquipped   = -1;
	Item m_weaponEquipped = -1;

	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetHealth() { return m_health; }
	void TakeDamage(int amount) { m_health -= amount;}
	void GainHealth(int amount) { m_health += amount;}

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	std::vector<int> m_playerStats;
};

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
	std::vector<Item> m_inventory = { Item(0), Item(1), Item(5), Item(6) };

	Item m_headEquipped   = Item(2);
	Item m_chestEquipped  = Item(3);
	Item m_legsEquipped   = Item(4);
	Item m_weaponEquipped = Item(5);

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
	void TakeDamage(int amount);
	void GainHealth(int amount)
	{
		m_health += amount;
		if (m_health > GetTotalVitality())
			m_health = GetTotalVitality();
	}

	int GetTotalStrength();
	int GetTotalDefense();
	int GetTotalDexterity();
	int GetTotalVitality();

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Update() override;
	virtual void Draw() override;
	virtual void HandleCollision(PlacableActor* collidedActor) override;

private:
	Key* m_pCurrentKey;
	std::vector<int> m_playerStats;
};

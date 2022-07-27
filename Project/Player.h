#pragma once
#include "PlacableActor.h"
#include <vector>
#include "PlayerDataManager.h"

class Key;

class Player : public PlacableActor
{
public:
	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	void AddMoney(int money) { m_money += money; PlayerDataManager::GetInstance()->UpdateValue(PlayerStats::MoneyTotal, m_money); }
	int GetMoney() { return m_money; }

	int GetHealth() { return m_health; }
	void TakeDamage(int amount) { m_health -= amount; PlayerDataManager::GetInstance()->UpdateValue(PlayerStats::Health, m_health); }
	void GainHealth(int amount) { m_health += amount; PlayerDataManager::GetInstance()->UpdateValue(PlayerStats::Health, m_health); }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_health;
	std::vector<int> m_playerStats;
};

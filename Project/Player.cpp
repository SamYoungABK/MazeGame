#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfHealth = 10;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_health(kStartingNumberOfHealth)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	cout << "@";
}

int Player::GetTotalStrength()
{
	int result = m_strength;
	result += m_headEquipped.GetStrength();
	result += m_chestEquipped.GetStrength();
	result += m_legsEquipped.GetStrength();
	result += m_weaponEquipped.GetStrength();

	return result;
}

int Player::GetTotalDefense()
{
	int result = m_defense;
	result += m_headEquipped.GetDefense();
	result += m_chestEquipped.GetDefense();
	result += m_legsEquipped.GetDefense();
	result += m_weaponEquipped.GetDefense();

	return result;
}

int Player::GetTotalDexterity()
{
	int result = m_dexterity;
	result += m_headEquipped.GetDexterity();
	result += m_chestEquipped.GetDexterity();
	result += m_legsEquipped.GetDexterity();
	result += m_weaponEquipped.GetDexterity();

	return result;
}

int Player::GetTotalVitality()
{
	int result = m_vitality;
	result += m_headEquipped.GetVitality();
	result += m_chestEquipped.GetVitality();
	result += m_legsEquipped.GetVitality();
	result += m_weaponEquipped.GetVitality();

	return result;
}
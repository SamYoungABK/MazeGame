#include "PlayerDataManager.h"

PlayerDataManager* PlayerDataManager::s_pInstance = nullptr;

void PlayerDataManager::UpdateValue(PlayerStats varName, int value)
{
	m_values[varName] = value;
}
#pragma once
#include <windows.h>
#include <vector>

enum PlayerStats : int {
	Money = 0,
	Health = 1,
	Strength = 2,
	Dexterity = 3,
	Vitality = 4
};

class PlayerDataManager
{
	static PlayerDataManager* s_pInstance;


	PlayerDataManager() { }

public:

	std::vector<int> m_values = { 0, 10, 2, 1, 10};

	static PlayerDataManager* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new PlayerDataManager();
		}
		return s_pInstance;
	}



	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}
	void UpdateValue(PlayerStats valName, int value);
	int GetValue(PlayerStats valName) { return m_values[valName]; };
};
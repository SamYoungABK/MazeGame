#pragma once
#include <vector>
#include <string>
#include <iterator>
#include "SelectionMenu.h"

class CustomLevelManager
{
	static CustomLevelManager* s_pInstance;

public:
	std::vector<std::string>* m_levelList = new std::vector<std::string>();
	std::vector<std::string>::iterator m_selectedLevel;
	

	bool m_loadCustomLevel = false;

	static CustomLevelManager* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new CustomLevelManager();
		}
		return s_pInstance;
	}
	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void BuildLevelList();
	char IsLevelSelected(std::string levelName);
	void MoveCursorUp();
	void MoveCursorDown();
	void DrawLevelList();
};


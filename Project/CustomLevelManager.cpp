#include "CustomLevelManager.h"

#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <vector>
#include <iterator>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

using std::experimental::filesystem::directory_iterator;
using std::cout; using std::endl;
using std::vector; using std::string;

CustomLevelManager* CustomLevelManager::s_pInstance = nullptr;

void CustomLevelManager::DrawLevelList()
{
	for (const auto& levelName : *m_levelList)
	{
		cout << "           " << IsLevelSelected(levelName) << " " << levelName << endl;
	}
}

void CustomLevelManager::BuildLevelList()
{
	string p = "../CustomLevels/";
	vector<string> result;

	delete m_levelList;
	m_levelList = new std::vector<std::string>;

	for (const auto& entry : directory_iterator(p))
	{
		string filename = entry.path().filename().string();
		m_levelList->push_back(filename);
	}
	m_selectedLevel = m_levelList->begin();
}

char CustomLevelManager::IsLevelSelected(string levelName)
{
	if (*m_selectedLevel == levelName)
		return '*';
	else
		return ' ';
}

void CustomLevelManager::MoveCursorUp()
{
	if (m_selectedLevel == m_levelList->begin()) return;

	m_selectedLevel--;
}

void CustomLevelManager::MoveCursorDown()
{
	if (m_selectedLevel + 1 == m_levelList->end()) return;

	m_selectedLevel++;
}

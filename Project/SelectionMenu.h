#pragma once
#include <string>
#include <vector>

class SelectionMenu
{
	std::vector<std::string> m_optionList = {};
	std::vector<std::string>::iterator m_optionListSelection;
public:
	SelectionMenu(std::vector<std::string> optionListPtr):
		m_optionList(optionListPtr)
	{
		m_optionListSelection = m_optionList.begin();
	};

	void MoveCursorUp();
	void MoveCursorDown();
	void PrintOptions();
	char IsOptionSelected(std::string optionName);

	~SelectionMenu()
	{};
};


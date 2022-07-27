#include "SelectionMenu.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

void SelectionMenu::MoveCursorUp()
{
	if (m_optionListSelection == m_optionList.begin()) return;

	m_optionListSelection--;
}

void SelectionMenu::MoveCursorDown()
{
	if (m_optionListSelection+1 == m_optionList.end()) return;

	m_optionListSelection++;
}

char SelectionMenu::IsOptionSelected(string optionName)
{
	if (*m_optionListSelection == optionName) return '*';
	return ' ';
}

void SelectionMenu::PrintOptions()
{
	for (const auto& option : m_optionList)
	{
		cout << "           " << IsOptionSelected(option) << " " << option << endl;
	}
}
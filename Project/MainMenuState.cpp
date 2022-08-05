#include "MainMenuState.h"

#include <iostream>
#include <conio.h>
#include "Renderer.h"
#include "RenderObject.h"
#include "TextObj.h"

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kLevelSelect = '4';
constexpr char kQuit = '5';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

bool MainMenuState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
		else if ((char)input == kHighScore)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::HighScore);
		}
		else if ((char)input == kLevelSelect)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::LevelSelect);
		}
		else if ((char)input == kSettings)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
	}
	return shouldQuit;
}

void MainMenuState::Draw()
{
	if (!Renderer::IsQueueEmpty()) return;
	Renderer::PushRenderObject(new TextObj("- - - MAIN MENU - - -", 100, 100));
	Renderer::PushRenderObject(new TextObj(". Play ", 100, 200));
	Renderer::PushRenderObject(new TextObj(". High Score", 100, 300));
	Renderer::PushRenderObject(new TextObj(". Settings ", 100, 400));
	Renderer::PushRenderObject(new TextObj(". Level Select ", 100, 500));
	Renderer::PushRenderObject(new TextObj(". Quit ", 100, 600));
	Renderer::GetInstance()->_shouldRender = true;
	//system("cls");
	//cout << endl << endl << endl;
	//cout << "          - - - MAIN MENU - - -" << endl << endl;
	//cout << "             " << kPlay << ". Play " << endl;
	//cout << "             " << kHighScore << ". High Score " << endl;
	//cout << "             " << kSettings << ". Settings " << endl;
	//cout << "             " << kLevelSelect << ". Level Select " << endl;
	//cout << "             " << kQuit << ". Quit " << endl;
}
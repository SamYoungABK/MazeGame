#include "Renderer.h"
#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include "CustomLevelManager.h"
#include "StateMachineExampleGame.h"
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>

#include "RenderObject.h"
#include "TextObj.h"

Game myGame;
StateMachineExampleGame gameStateMachine(&myGame);


LRESULT CALLBACK WndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	myGame.Initialize(&gameStateMachine);
	HWND hWnd;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"GameWindow";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL,
		L"GameWindow",
		L"Maze Game",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	myGame.Deinitialize();

	AudioManager::DestroyInstance();
	CustomLevelManager::DestroyInstance();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	myGame.RunGameLoop();

	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	case WM_PAINT:
	{
		Renderer::Render(hWnd);
		return 0L;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

using namespace std;

//int main()
//{
//	Game myGame;
//
//	StateMachineExampleGame gameStateMachine(&myGame);
//
//	myGame.Initialize(&gameStateMachine);
//
//	myGame.RunGameLoop();
//
//	myGame.Deinitialize();
//
//	AudioManager::DestroyInstance();
//	CustomLevelManager::DestroyInstance();
//	return 0;
//}
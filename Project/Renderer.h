#pragma once
#include <queue>
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include "RenderObject.h"

using std::queue;

class Renderer
{
	static Renderer* _instance;
	

	queue<RenderObject*> renderQueue;

	/*void DrawObject(HWND hWnd, RenderObject* obj);
	void DrawText(HWND hWnd);*/

public:
	bool _shouldRender;
	Renderer() :
		_shouldRender(false)
	{};

	static Renderer* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Renderer();
		}
		return _instance;
	}

	static void PushRenderObject(RenderObject* obj) { GetInstance()->renderQueue.push(obj); };
	static bool IsQueueEmpty() { return GetInstance()->renderQueue.empty(); }
	static void Render(HWND hWnd);
};
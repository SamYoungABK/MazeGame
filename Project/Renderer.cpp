#include "Renderer.h"
#include "RenderObject.h"

#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>

#include <queue>

using std::queue;

Renderer* Renderer::_instance = nullptr;

//void Renderer::DrawObject(HWND hWnd, RenderObject* obj)
//{
//	PAINTSTRUCT ps;
//	BeginPaint(hWnd, &ps);
//
//	RECT rc;
//	GetClientRect(
//		hWnd,
//		&rc
//	);
//
//	HGDIOBJ original = NULL;
//	{
//		original = SelectObject(
//			ps.hdc,
//			GetStockObject(DC_PEN)
//		);
//	}
//
//	if (obj->GetType() == renderObjectType::TEXT)
//	{
//		SelectObject(ps.hdc, defaultFont);
//		TextOut(ps.hdc, rc.left + 100, rc.top + 100, L"MAZE GAME", 10);
//	}
//}

void Renderer::Render(HWND hWnd)
{
	Renderer* inst = GetInstance();
	if (!inst->_shouldRender) return;

	while (!inst->renderQueue.empty())
	{
		inst->renderQueue.front()->draw(hWnd);
		inst->renderQueue.pop();
	}
	inst->_shouldRender = false;
		

	//HPEN blackPen = CreatePen(HS_CROSS, 5, 0x0000FF);
	//HFONT redFont = CreateFontA(32, 16, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//SelectObject(ps.hdc, blackPen);

	//Rectangle(ps.hdc, rc.left + 100, rc.top + 100, rc.right - 100, rc.bottom - 100);

	//SelectObject(ps.hdc, redFont);
	//TextOut(ps.hdc, rc.left + 100, rc.top + 100, L"MAZE GAME", 10);

	//DeleteObject(blackPen);

	//SelectObject(ps.hdc, original);

	//EndPaint(hWnd, &ps);
}
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>

#include "RenderObject.h"
#include "TextObj.h"

#include <string>

using std::string;

void TextObj::draw(HWND hWnd)
{	
	BeginPaint(hWnd, &_ps);
	SelectObject(_ps.hdc, _fontObj);
	TextOutA(_ps.hdc, _x, _y, _text.c_str(), _text.size());
	EndPaint(hWnd, &_ps);
}

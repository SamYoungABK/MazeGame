#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>


enum renderObjectType
{
	TEXT = 0,
};

class RenderObject
{
	renderObjectType _type;
public:
	renderObjectType GetType() { return _type; }
	virtual void draw(HWND hWnd) = 0;
};
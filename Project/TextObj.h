#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <gdiplus.h>

#include "RenderObject.h"
#include "TextObj.h"

#include <string>

using std::string;

static HFONT defaultFont = CreateFontA(32, 16, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0);
static PAINTSTRUCT defaultPs{};

class TextObj :
    public RenderObject
{
    string _text = nullptr;
    int _x = 0;
    int _y = 0;
    PAINTSTRUCT _ps;
    HFONT _fontObj = NULL;

public:
    TextObj(string text, int x, int y, PAINTSTRUCT ps=defaultPs, HFONT fontObj=defaultFont) :
        _text(text),
        _x(x),
        _y(y),
        _ps(ps),
        _fontObj(fontObj) {};

    virtual void draw(HWND hWnd) override;
};


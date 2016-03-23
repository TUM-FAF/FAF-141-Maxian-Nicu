#include "stdafx.h"
#include "Line.h"


Line::Line()
{
}


Line::~Line()
{
}

void Line::draw(HDC &hdc)
{
	MoveToEx(hdc, start.x, start.y, NULL);
	LineTo(hdc, end.x, end.y);
}
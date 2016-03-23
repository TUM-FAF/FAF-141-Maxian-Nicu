#include "stdafx.h"
#include "Eraser.h"


Eraser::Eraser() : MultiPointDrawing()
{
	setColor(RGB(255, 255, 255));
}


Eraser::~Eraser()
{
}

void Eraser::draw(HDC& hdc)
{
	COLORREF COLOR = RGB(255, 255, 255);
	SelectObject(hdc, CreatePen(this->penStyle, this->penWidth, COLOR));
	SelectObject(hdc, CreateSolidBrush(COLOR));
	for (int i = 0; i < count; i++)
	{
		RECT rect;
		rect.left = points[i].x - penWidth;
		rect.right = points[i].x + penWidth;
		rect.top = points[i].y - penWidth;
		rect.bottom = points[i].y + penWidth;
		Ellipse(
			hdc,
			rect.left,
			rect.top,
			rect.right,
			rect.bottom
			);
	}
}

void Eraser::onClick(POINT p)
{
	if (!finished){
		if (!started)
		{
			started = true;
		}
		else
			finished = true;
		addPoint(p);
	}
}

void Eraser::onMove(POINT p)
{
	addPoint(p);
}


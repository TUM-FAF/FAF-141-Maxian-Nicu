#include "stdafx.h"
#include "Rectangle.h"


RectangleDrawing::RectangleDrawing()
{
}


RectangleDrawing::~RectangleDrawing()
{
}


void RectangleDrawing::draw(HDC& hdc)
{
	RECT Recto = { start.x,start.y,end.x,end.y };

	DrawEdge(hdc, &Recto, BDR_RAISEDOUTER | BDR_SUNKENINNER, BF_RECT);
}

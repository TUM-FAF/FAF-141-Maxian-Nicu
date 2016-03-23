#include "stdafx.h"
#include "PolygonDrawing.h"


PolygonDrawing::PolygonDrawing()
{
}


PolygonDrawing::~PolygonDrawing()
{
}

void PolygonDrawing::draw(HDC& hdc)
{
	if (count > 0){
		MoveToEx(hdc, points[0].x, points[0].y, NULL);
		for (int i = 0; i < count; i++)
		{
			LineTo(hdc, points[i].x, points[i].y);
		}
		LineTo(hdc, points[0].x, points[0].y);
	}
}

void PolygonDrawing::onClick(POINT p)
{
	if (!finished){
		if (!started)
		{
			started = true;
		}
		if (movingIndex != -1){
			points[movingIndex] = p;
		} 
		else
			addPoint(p);
		movingIndex = -1;
	}
}

void PolygonDrawing::onMove(POINT p)
{
	if (movingIndex == -1){
		movingIndex = count;
		addPoint(p);
	}
	else
		points[movingIndex] = p;
}
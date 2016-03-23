#include "stdafx.h"
#include "Bezier.h"


BezierDrawing::BezierDrawing()
{
}


BezierDrawing::~BezierDrawing()
{
}

void BezierDrawing::draw(HDC& hdc)
{
	PolyBezier(hdc, points, count);
}

void BezierDrawing::onClick(POINT p)
{
	if (!finished){
		if (!started)
		{
			started = true;
		}
		addPoint(p);
	}
}

void BezierDrawing::onMove(POINT p)
{
}

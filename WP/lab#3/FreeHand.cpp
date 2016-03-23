#include "stdafx.h"
#include "FreeHand.h"


FreeHand::FreeHand()
{
}


FreeHand::~FreeHand()
{
}

void FreeHand::draw(HDC& hdc)
{
	if (count > 0){
		MoveToEx(hdc, points[0].x, points[0].y, NULL);
		for (int i = 0; i < count; i++)
		{
			LineTo(hdc, points[i].x, points[i].y);
		}
	}
}

void FreeHand::onClick(POINT p)
{
	if (!started)
	{
		started = true;
	} else
	{
		started = false;
		finished = true;
	}
}

void FreeHand::onMove(POINT p)
{
	addPoint(p);
}

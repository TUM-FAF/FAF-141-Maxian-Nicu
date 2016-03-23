#include "stdafx.h"
#include "MultiPointDrawing.h"


MultiPointDrawing::MultiPointDrawing()
{
	count = 0;
	finished = started = false;
	movingIndex = -1;
}


MultiPointDrawing::~MultiPointDrawing()
{
}

bool MultiPointDrawing::isFinished()
{
	return finished;
}

void MultiPointDrawing::addPoint(POINT p)
{
	POINT *newPoints = new POINT[count + 1];
	for (int i = 0; i < count; i++)
	{
		newPoints[i] = points[i];
	}
	count++;
	if (points != NULL)
		delete[] points;
	points = newPoints;
	points[count - 1] = p;
}

void MultiPointDrawing::onInterrupt()
{
	finished = true;
	if (movingIndex != -1)
		count--;
}

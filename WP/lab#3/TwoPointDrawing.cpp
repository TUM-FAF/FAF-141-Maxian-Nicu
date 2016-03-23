#include "stdafx.h"
#include "TwoPointDrawing.h"


TwoPointDrawing::TwoPointDrawing() : Drawing()
{
	started = finished = false;
}


TwoPointDrawing::~TwoPointDrawing()
{
}

void TwoPointDrawing::onClick(POINT p)
{
	if (!started)
	{
		start = p;
		started = true;
	}
	else
	{
		finished = true;
		end = p;
	}
}

bool TwoPointDrawing::isFinished()
{
	return finished;
}

void TwoPointDrawing::onMove(POINT p)
{
	end = p;
}

void TwoPointDrawing::onInterrupt()
{
}

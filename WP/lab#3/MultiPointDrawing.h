#pragma once
#include "Drawing.h"
class MultiPointDrawing :
	public Drawing
{
protected:
	int count;
	POINT *points;
	bool finished;
	bool started;
	int movingIndex;
	void addPoint(POINT p);
public:
	MultiPointDrawing();
	~MultiPointDrawing();
	bool isFinished() override;
	void onInterrupt() override;
};


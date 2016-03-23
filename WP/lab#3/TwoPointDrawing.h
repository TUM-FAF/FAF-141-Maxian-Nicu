#pragma once
#include "Drawing.h"
class TwoPointDrawing :
	public Drawing
{
protected:
	bool started;
	bool finished;
	POINT start;
	POINT end;
public:
	TwoPointDrawing();
	~TwoPointDrawing();
	void onClick(POINT p) override;
	bool isFinished() override;
	void onMove(POINT p) override;
	void onInterrupt() override;
};


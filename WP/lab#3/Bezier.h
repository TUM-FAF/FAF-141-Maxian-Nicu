#pragma once
#include "MultiPointDrawing.h"
#include <wincon.h>

class BezierDrawing :
	public MultiPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	BezierDrawing();
	~BezierDrawing();
	void onClick(POINT p) override;
	void onMove(POINT p) override;
};


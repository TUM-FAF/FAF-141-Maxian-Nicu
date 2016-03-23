#pragma once
#include "MultiPointDrawing.h"
class PolygonDrawing :
	public MultiPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	PolygonDrawing();
	~PolygonDrawing();
	void onClick(POINT p) override;
	void onMove(POINT p) override;
};


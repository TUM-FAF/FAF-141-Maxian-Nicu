#pragma once
#include "MultiPointDrawing.h"

class Eraser : public MultiPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	Eraser();
	~Eraser();
	void onClick(POINT p) override;
	void onMove(POINT p) override;
};


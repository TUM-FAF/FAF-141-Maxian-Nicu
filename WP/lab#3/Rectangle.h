#pragma once
#include "TwoPointDrawing.h"
class RectangleDrawing :
	public TwoPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	RectangleDrawing();
	~RectangleDrawing();
};


#pragma once
#include "Drawing.h"
#include "TwoPointDrawing.h"

class Line :
	public TwoPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	Line();
	~Line();

};


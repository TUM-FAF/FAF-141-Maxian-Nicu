#pragma once
#include <wincon.h>
#include "TwoPointDrawing.h"

class EllipseDrawing :
	public TwoPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	EllipseDrawing();
	~EllipseDrawing();
};


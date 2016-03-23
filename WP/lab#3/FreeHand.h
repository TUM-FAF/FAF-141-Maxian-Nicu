#pragma once
#include "Drawing.h"
#include "MultiPointDrawing.h"

class FreeHand :
	public MultiPointDrawing
{
protected:
	void draw(HDC &hdc) override;
public:
	FreeHand();
	~FreeHand();
	void onClick(POINT p) override;
	void onMove(POINT p) override;
};


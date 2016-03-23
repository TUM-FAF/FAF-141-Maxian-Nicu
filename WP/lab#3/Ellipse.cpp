#include "stdafx.h"
#include "Ellipse.h"


EllipseDrawing::EllipseDrawing() : TwoPointDrawing()
{

}


EllipseDrawing::~EllipseDrawing()
{
}

void EllipseDrawing::draw(HDC &hdc)
{
	Ellipse(
		hdc,
		start.x,
		start.y,
		end.x,
		end.y
		);
}

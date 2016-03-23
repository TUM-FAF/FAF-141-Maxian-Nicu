#include "stdafx.h"
#include "Drawing.h"


Drawing::Drawing()
{
	this->penColor = RGB(255, 0, 0);
	this->penStyle = PS_SOLID;
	this->penWidth = 1;
	this->customPen = NULL;
}


Drawing::~Drawing()
{
}


void Drawing::onDraw(HDC &hdc)
{
	HPEN hPenOld;

	// Draw a red line
	HPEN hLinePen;
	hLinePen = getPen();
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);
	SelectObject(hdc, CreateSolidBrush(this->penColor));

	draw(hdc);


	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);
}

void Drawing::setWidth(int width)
{
	this->penWidth = width;
}

void Drawing::setStyle(int style)
{
	this->penStyle = style;
}

void Drawing::setColor(COLORREF color)
{
	this->penColor = color;
}

HPEN Drawing::getPen()
{
	if (customPen != NULL)
		return *customPen;
	return CreatePen(this->penStyle, this->penWidth, this->penColor);
}

void Drawing::setPen(HPEN pen)
{
	customPen = new HPEN;
	*customPen = pen;
}

void Drawing::increaseWidth()
{
	penWidth++;
}

void Drawing::decreaseWidth()
{
	penWidth--;
	if (penWidth < 1)
		penWidth = 1;
}

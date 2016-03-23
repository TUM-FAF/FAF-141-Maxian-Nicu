#include "stdafx.h"
#include "Pen.h"


Pen::Pen()
{
	this->style = PS_SOLID;
	this->width = 7;
	this->color = RGB(255, 0, 0);
}


Pen::~Pen()
{
}


void Pen::setStyle(int style){
	this->style = style;
	revalidate();
}

void Pen::setWidth(int width){
	this->width = width;
	revalidate();
}

void Pen::setColor(COLORREF color){
	this->color = color;
	revalidate();
}

void Pen::revalidate(){
	this->instance = CreatePen(this->style,this->width,this->color);
}
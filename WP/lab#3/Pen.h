#pragma once
class Pen
{
private:
	HPEN instance;
	int style;
	int width;
	COLORREF color;
	
	void revalidate();
public:
	Pen();
	~Pen();
	void setStyle(int style);
	void setWidth(int width);
	void setColor(COLORREF color);
};


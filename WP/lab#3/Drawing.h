#pragma once
class Drawing
{
protected:
	int penWidth;
	int penStyle;
	COLORREF penColor;
	HPEN getPen();
	HPEN *customPen;
	virtual void draw(HDC &hdc) = 0;
public:
	Drawing();
	~Drawing();
	void setWidth(int width);
	void increaseWidth();
	void decreaseWidth();
	void setStyle(int style);
	void setColor(COLORREF color);
	void onDraw(HDC &hdc);
	void setPen(HPEN pen);
	virtual void onInterrupt() = 0;
	virtual void onClick(POINT p) = 0;
	virtual void onMove(POINT p) = 0;
	virtual bool isFinished() = 0;
};


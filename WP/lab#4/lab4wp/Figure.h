#pragma once
#define CIRCLE 1
#define SQUARE 0

class Figure
{
private:
	int type;
	int radius;
	int x;
	int y;
	int velocityX;
	int velocityY;
	COLORREF color;

public:
	Figure(int radius,int x,int y);
	~Figure();
	void paint(HDC hdc);
	void setRandomColor();
	void setRandomVelocity();
	void setRandomRadius();
	void setSquare();
	void setCircle();
	void update();
	bool collides(Figure figure);
	bool collidesVerticalLine(int x);
	bool collidesHorizontalLine(int y);
	void invertVelocityX();
	void invertVelocityY();
	void increaseVelocity();
	void decreaseVelocity();
	void flipFigure();
	int getType();
	int getX();
	int getY();
	void setPosition(int x, int y);
};


#pragma once
class Point
{
public:
	Point(float _x, float _y);
	~Point();

	float getX();
	float getY();


private:
	float x, y;
};

Point::Point(float _x, float _y)
{
	x = _x;
	y = _y;
}


Point::~Point()
{
}

float Point::getX()
{
	return x;
}

float Point::getY()
{
	return y;
}


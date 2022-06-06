#pragma once



struct Point2f
{
	Point2f();
	explicit Point2f(float x, float y);

	float x;
	float y;
};

struct Rectanglef
{
	Rectanglef()
	{
		left = 0.f;
		bottom = 0.f;
		width = 0.f;
		height = 0.f;
	}
	Rectanglef(float _left, float _bottom, float _width, float _height):
		left{ _left },
		bottom{_bottom },
		width{ _width },
		height{ _height }
	{

	}

	float left;
	float bottom;
	float width;
	float height;

};


struct Color4f
{
	Color4f();
	explicit Color4f(float r, float g, float b, float a);

	float r;
	float g;
	float b;
	float a;
};
#pragma once
#include "Point.h"
#include "Line.h"


class Rectangle
{
	Point lb, ru;

public:
	Rectangle(Point l1, Point l2);
	Rectangle(Line l);

	Line getLeftSide();
	Line getRightSide();
	Line getBottomSide();
	Line getUpperSide();
};


#pragma once
#include "Point.h"
#include "Line.h"


class Rectangle
{
	Point lb, ru;

public:
	explicit Rectangle(coord_t x1, coord_t y1, coord_t x2, coord_t y2);
	explicit Rectangle(Point l1, Point l2);
	explicit Rectangle(Line l);

	Line getLeftSide();
	Line getRightSide();
	Line getBottomSide();
	Line getUpperSide();
};


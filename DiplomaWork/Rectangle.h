#pragma once
#include "Point.h"
#include "Line.h"


BEGIN_NAMESPACE(nm_Rectangle)
using namespace nm_Point;
using namespace nm_Line;

class Rectangle
{
	Point lb, ru;

public:
	explicit Rectangle(coord_t x1, coord_t y1, coord_t x2, coord_t y2);
	explicit Rectangle(Point l1, Point l2);
	explicit Rectangle(Line l);

	Line getLeftSide() const;
	Line getRightSide() const;
	Line getBottomSide() const;
	Line getUpperSide() const;
};

END_NAMESPACE(nm_Rectangle)
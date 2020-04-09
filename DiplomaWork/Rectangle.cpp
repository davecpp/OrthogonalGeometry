#include "Rectangle.h"
#include <boost/assert.hpp>

Rectangle::Rectangle(Point p1, Point p2) :
	Rectangle(Line(p1, p2))
{}

Rectangle::Rectangle(Line l) : lb(l.getLeftPoint()), ru(l.getRightPoint())
{
	BOOST_ASSERT_MSG(!(l.isHorizontal() || l.isVertical()),
		"Invalid rectangle format");

	coord_t left_x = l.getLeftPoint().getAbscis();
	coord_t right_x = l.getRightPoint().getAbscis();
	coord_t bottom_y = l.getBottomPoint().getOrdinate();
	coord_t upper_y = l.getUpperPoint().getOrdinate();

	lb = Point(left_x, bottom_y);
	ru = Point(right_x, upper_y);
}

Line Rectangle::getLeftSide()
{
	return Line(lb, lb.getAbscis(), ru.getOrdinate());
}

Line Rectangle::getRightSide()
{
	return Line(ru.getAbscis(), lb.getOrdinate(), ru);
}

Line Rectangle::getBottomSide()
{
	return Line(lb, ru.getAbscis(), lb.getOrdinate());
}

Line Rectangle::getUpperSide()
{
	return Line(lb.getAbscis(), ru.getOrdinate(), ru);
}



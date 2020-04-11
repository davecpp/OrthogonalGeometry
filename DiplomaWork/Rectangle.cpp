#include "Rectangle.h"
#include <boost/assert.hpp>

BEGIN_NAMESPACE(nm_Rectangle)

Rectangle::Rectangle(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :
	lb(std::min(x1, x2), std::min(y1, y2)),
	ru(std::max(x1, x2), std::max(y1, y2))
{
	/*BOOST_ASSERT_MSG(!(Line(lb,ru).isHorizontal() || Line(lb,ru).isVertical()),
		"Invalid rectangle format");*/
	BOOST_ASSERT_MSG(!(x1 == x2/*vertical*/ || y1 == y2/*horizontal*/),
		"Invalid rectangle format");
}

Rectangle::Rectangle(Point p1, Point p2) :
	Rectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY())
{}

Rectangle::Rectangle(Line l) :
	Rectangle(l.firstPoint(), l.secondPoint())
{}


Line Rectangle::getLeftSide() const
{
	return Line(lb, lb.getAbscis(), ru.getOrdinate());
}

Line Rectangle::getRightSide() const
{
	return Line(ru.getAbscis(), lb.getOrdinate(), ru);
}

Line Rectangle::getBottomSide() const
{
	return Line(lb, ru.getAbscis(), lb.getOrdinate());
}

Line Rectangle::getUpperSide() const
{
	return Line(lb.getAbscis(), ru.getOrdinate(), ru);
}


END_NAMESPACE(nm_Rectangle)
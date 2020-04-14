#include "Rectangle.h"
#include <boost/assert.hpp>

BEGIN_NAMESPACE(nm_Rectangle)

namespace PointOperations {
	inline bool operator>(Point p1, Point p2) {
		return p1.getX() > p2.getX() && p1.getY() > p2.getY();
	}
	inline bool operator>=(Point p1, Point p2) {
		return p1.getX() >= p2.getX() && p1.getY() >= p2.getY();
	}

	inline bool operator<(Point p1, Point p2) {
		return p1.getX() < p2.getX() && p1.getY() < p2.getY();
	}
	inline bool operator<=(Point p1, Point p2) {
		return p1.getX() <= p2.getX() && p1.getY() <= p2.getY();
	}
}


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

bool Rectangle::ContainsPoint(Point p) const
{
	return p.getX() >= lb.getX() && p.getX() <= ru.getX()
		&& p.getY() >= lb.getY() && p.getY() <= ru.getY();

}

bool Rectangle::ContainsLine(Line l) const
{
	return ContainsPoint(l.firstPoint()) && ContainsPoint(l.secondPoint());
}

bool Rectangle::areIntersect(Line l) const
{
	return Line::VerticalLineIntersection(getLeftSide(), l).has_value() ||
		Line::VerticalLineIntersection(getRightSide(), l).has_value() ||
		Line::HorizontalLineIntersection(getUpperSide(), l).has_value() ||
		Line::HorizontalLineIntersection(getBottomSide(), l).has_value();
}






bool Rectangle::areIntersect(Rectangle r1, Rectangle r2)
{
	using namespace PointOperations;
	return r1.ru >= r2.lb && r2.ru >= r1.lb;
}








END_NAMESPACE(nm_Rectangle)
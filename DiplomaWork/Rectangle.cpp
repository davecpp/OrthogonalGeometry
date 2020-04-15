
#include <boost/assert.hpp>
#include "Rectangle.h"


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

Point Rectangle::LeftBottom() const
{
	return lb;
}

Point Rectangle::LeftUpper() const
{
	return Point(left_X(), upper_Y());
}

Point Rectangle::RightBottom() const
{
	return Point(right_X(), bottom_Y());
}

Point Rectangle::RightUpper() const
{
	return ru;
}

distance_t Rectangle::width() const
{
	return max_X() - min_X();
}

distance_t Rectangle::height() const
{
	return max_Y() - min_Y();
}

area_t Rectangle::Area() const
{
	return height() * width();
}

distance_t Rectangle::Perimetr() const
{
	return 2 * height() + 2 * width();
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

std::optional<Line> Rectangle::commonLine(Line l) const
{
	const Point invalid_point = Point(invalid_coord, invalid_coord);
	Point x[2] = { invalid_point,invalid_point };

	auto push_back = [&x, invalid_point](std::optional<Point> p) {
		if (p.has_value()) {
			if (x[0] == invalid_point)
				x[0] = p.value();
			else if (x[1] == invalid_point && p.value() != x[0])
				x[1] = p.value();
		}
	};

	push_back(Line::VerticalLineIntersection(getLeftSide(), l));
	push_back(Line::VerticalLineIntersection(getRightSide(), l));
	push_back(Line::HorizontalLineIntersection(getUpperSide(), l));
	push_back(Line::HorizontalLineIntersection(getBottomSide(), l));

	BOOST_ASSERT_MSG(x[0] == invalid_point && x[1] != invalid_point, "impl error in lambda function");

	if (x[0] == invalid_point /*&& x[1] == invalid_point*/) //intersect in 0 points
		return ContainsPoint(l.firstPoint()) ? l : std::optional<Line>();
	else if (x[1] == invalid_point/* && x[0] != invalid*/)  //intersect in 1 points
		return ContainsPoint(l.firstPoint()) ? Line(x[0], l.firstPoint()) : Line(x[0], l.secondPoint());
	else return Line(x[0], x[1]); //intersect in 2 points
}






bool Rectangle::areIntersect(Rectangle r1, Rectangle r2)
{
	using namespace PointOperations;
	return r1.ru >= r2.lb && r2.ru >= r1.lb;
}

bool Rectangle::areIntersectInRect(Rectangle r1, Rectangle r2)
{
	using namespace PointOperations;
	return r1.ru > r2.lb && r2.ru > r1.lb;
}


std::optional<Rectangle> Rectangle::IntersectionRect(Rectangle r1, Rectangle r2)
{
	/*if (!areIntersectInRect(r1, r2))
		return std::optional<Rectangle>();*/
	auto rangeX = range::range_X(r1.getBottomSide(), r2.getBottomSide());
	auto rangeY = range::range_Y(r1.getLeftSide(), r2.getLeftSide());
	if (rangeX.has_value() && rangeY.has_value())
		return Rectangle(rangeX.value().min, rangeY.value().min, rangeX.value().max, rangeY.value().max);
	return std::optional<Rectangle>();
}








END_NAMESPACE(nm_Rectangle)
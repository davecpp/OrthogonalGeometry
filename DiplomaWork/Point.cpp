#include "Point.h"
#include <complex>

//value^2
template<typename _Ty>
auto square(_Ty value)->decltype(value* value)
{
	return value * value;
}

distance_t Point::distance(Point p1, Point p2)
{
	return std::sqrt(square(delta_x(p2, p1)) + square(delta_y(p2, p1)));
}

coord_t Point::delta_x(Point p1, Point p2)
{
	return p1.getX() - p2.getX();
}

coord_t Point::delta_y(Point p1, Point p2)
{
	return p1.getY() - p2.getY();
}

std::pair<Point, Point> Point::minmax_X(Point p1, Point p2)
{
	return p1.getX() < p2.getX() ? std::pair(p1, p2) : std::pair(p2, p1);
}


std::pair<Point, Point> Point::minmax_Y(Point p1, Point p2)
{
	return p1.getY() < p2.getY() ? std::pair(p1, p2) : std::pair(p2, p1);
}

//x
coord_t Point::getAbscis() { return x; }
//y
coord_t Point::getOrdinate() { return y; }
//abscis
coord_t Point::getX() { return getAbscis(); }
//ordinate
coord_t Point::getY() { return getOrdinate(); }

//setters//////////////////////////////

//x
inline void Point::setAbscis(coord_t abscis) { x = abscis; }
//y
inline void Point::setOrdinate(coord_t ordinate) { y = ordinate; }
//abscis
inline void Point::setX(coord_t x) { setAbscis(x); }
//ordinate
inline void Point::setY(coord_t y) { setOrdinate(y); }


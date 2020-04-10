#include "Point.h"
#include <complex>

//value^2
template<typename _Ty>
auto square(_Ty value)->decltype(value* value)
{
	return value * value;
}
//distance between p1 and p2 (result >=0)
distance_t Point::distance(Point p1, Point p2)
{
	return std::sqrt(square(delta_x(p2, p1)) + square(delta_y(p2, p1)));
}
//p1.x - p2.x
coord_t Point::delta_x(Point p1, Point p2)
{
	return p1.getX() - p2.getX();
}
//p1.y - p2.y
coord_t Point::delta_y(Point p1, Point p2)
{
	return p1.getY() - p2.getY();
}

//first element min(p1.x,p2.x), second other
std::pair<Point, Point> Point::minmax_X(Point p1, Point p2)
{
	return p1.getX() < p2.getX() ? std::pair(p1, p2) : std::pair(p2, p1);
}

//first element min(p1.y,p2.y), second other
std::pair<Point, Point> Point::minmax_Y(Point p1, Point p2)
{
	return p1.getY() < p2.getY() ? std::pair(p1, p2) : std::pair(p2, p1);
}

//x
coord_t Point::getAbscis() const { return x; }
//y
coord_t Point::getOrdinate() const { return y; }
//abscis
coord_t Point::getX() const { return getAbscis(); }
//ordinate
coord_t Point::getY() const { return getOrdinate(); }

//setters//////////////////////////////

//x
inline void Point::setAbscis(coord_t abscis) { x = abscis; }
//y
inline void Point::setOrdinate(coord_t ordinate) { y = ordinate; }
//abscis
inline void Point::setX(coord_t x) { setAbscis(x); }
//ordinate
inline void Point::setY(coord_t y) { setOrdinate(y); }


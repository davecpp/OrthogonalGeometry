#pragma once
#include <utility>
#include <limits>
#include "BadCoordinate.h"



using coord_t = double;
using distance_t = double;


BEGIN_NAMESPACE(nm_Point)
//constexpr coord_t invalid_coord = std::numeric_limits<coord_t>::lowest();
const coord_t invalid_coord = nan("invalid coordinate");



class Point
{
	//default is invalid(nullopt)
	coord_t x, y;

public:
	//by default invalid
	explicit Point(coord_t x, coord_t y) :x(x), y(y) {}

	NODISCARD bool isValid() {
		return x != invalid_coord && y != invalid_coord;
	}
	//distance between p1 and p2 (result>=0)
	NODISCARD static distance_t distance(Point p1, Point p2);
	//p1.x - p2.x
	static coord_t delta_x(Point p1, Point p2);
	//p1.y - p2.y
	static coord_t  delta_y(Point p1, Point p2);

	//return pair, first point is min_abscis(p1,p2) 
	NODISCARD static std::pair<Point, Point> minmax_X(Point p1, Point p2);
	//return pair, first point is min_ordinate(p1,p2) 
	NODISCARD static std::pair<Point, Point> minmax_Y(Point p1, Point p2);

	//getters/////////////////////////////

	//x
	coord_t getAbscis() const;
	//y
	coord_t getOrdinate() const;
	//abscis
	coord_t getX() const;
	//ordinate
	coord_t getY() const;

	//setters//////////////////////////////

	//x
	inline void setAbscis(coord_t abscis);
	//y
	inline void setOrdinate(coord_t ordinate);
	//abscis
	inline void setX(coord_t x);
	//ordinate
	inline void setY(coord_t y);
};

NODISCARD bool operator==(Point p1, Point p2);
NODISCARD bool operator!=(Point p1, Point p2);

END_NAMESPACE(nm_Point)
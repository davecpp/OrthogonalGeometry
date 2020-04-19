#pragma once
#include <utility>
#include <limits>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include "BadCoordinate.h"
#include "GeometryCast.h"



//value^2
template<typename _Ty>
auto square(_Ty value)->decltype(value* value)
{
	return value * value;
}

BEGIN_GEOMETRY
using coord_t = double;
using distance_t = decltype(coord_t() - coord_t());

namespace c_axis {
	enum coordinate_axis_type : size_t {
		x = 0,
		y = 1,
		abscis = x,
		ordinate = y
	};
}
END_GEOMETRY


namespace bg = boost::geometry;




IN_NAEMSPACE_GEOMETRY(nm_Point)
//constexpr coord_t invalid_coord = std::numeric_limits<coord_t>::lowest();
const coord_t invalid_coord = nan("invalid coordinate");


using boost_point = boost::geometry::model::point<coord_t, 2, bg::cs::cartesian>;

class Point
{
	//default is invalid(nullopt)
	coord_t x, y;

public:
	//for boost compatibility
	Point(boost_point p) :x(p.get<c_axis::x>()), y(p.get<c_axis::y>()) {}
	/*explicit*/ operator boost_point() const {
		return boost_point(x, y);
	}
	/////////////////////////


	//by default invalid
	explicit Point(coord_t x, coord_t y) :x(x), y(y) {}

	NODISCARD bool isValid() const {
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
	void setAbscis(coord_t abscis);
	//y
	void setOrdinate(coord_t ordinate);
	//abscis
	void setX(coord_t x);
	//ordinate
	void setY(coord_t y);
};



NODISCARD bool operator==(Point p1, Point p2);
NODISCARD bool operator!=(Point p1, Point p2);

END_NAMESPACE_GEOMETRY(nm_Point)
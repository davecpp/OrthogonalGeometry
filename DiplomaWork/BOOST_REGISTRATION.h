/*
#pragma once
#include <boost/geometry/geometries/geometries.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/segment.hpp>
#include <boost/geometry/geometries/register/box.hpp>


#include "Point.h"
#include "Line.h"
#include "Rectangle.h"

ANONYM_NAMESPACE


//namespace c_axis {
//	enum coordinate_axis_type : size_t {
//		x = 0,
//		y = 1,
//		abscis = x,
//		ordinate = y
//	};
//}



namespace bg = boost::geometry;
using namespace nm_Point;
using namespace nm_Rectangle;
using namespace nm_Line;

using namespace bg;



using boost_point = bg::model::point<coord_t, 2, cs::cartesian>;
using boost_line = boost::geometry::model::segment<boost_point>;
using boost_rectangle = boost::geometry::model::box<boost_point>;
using boost_polygon = boost::geometry::model::polygon<boost_point>;


boost_point point(nm_Point::Point p) {
	return boost_point(p.getX(), p.getY());
}

boost_line line(nm_Line::Line l) {
	return boost_line(point(l.firstPoint()), point(l.secondPoint()));
}


boost_rectangle rectangle(nm_Rectangle::Rectangle r) {
	return boost_rectangle(point(r.LeftBottom()), point(r.RightUpper()));
}


nm_Point::Point toPoint(boost_point p) {
	return nm_Point::Point(p.get<0>(), p.get<1>());
}

nm_Line::Line toLine(boost_line l) {
	return nm_Line::Line(toPoint(l.first), toPoint(l.second));
}

nm_Rectangle::Rectangle toRectangle(boost_rectangle r) {
	return nm_Rectangle::Rectangle(toPoint(r.min_corner()), toPoint(r.max_corner()));
}




END_NAMESPACE_GEOMETRY(ANONYM);
*/

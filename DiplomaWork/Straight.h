#pragma once
#include "Straight_Abstract.h"
#include "StraightEquation.h"
#include "p_Straight.h"




template<>
inline nm_Straight::StraightEquation geometry_cast<nm_Straight::StraightEquation>(nm_Straight::p_Straight s) {
	//http://www.math.by/geometry/eqline.html

	coord_t a = nm_Point::Point::delta_y(s.firstPoint(), s.secondPoint());
	coord_t b = nm_Point::Point::delta_x(s.secondPoint(), s.firstPoint());
	coord_t c = s.firstPoint().getX() * s.secondPoint().getY() - s.firstPoint().getY() * s.secondPoint().getX();
	return nm_Straight::StraightEquation(a, b, c);
}


template<>
inline nm_Straight::p_Straight geometry_cast<nm_Straight::p_Straight>(nm_Straight::StraightEquation e) {
	return nm_Straight::p_Straight(
		nm_Point::Point(0, e.getY(0)),
		nm_Point::Point(10, e.getY(10))
	);
}
/*

template<>
inline nm_Straight::p_Straight geometry_cast<nm_Straight::p_Straight>(nm_Vector::Vector v) {
	return nm_Straight::p_Straight(v.VectorBegin(), v.VectorEnd());
}

template<>
inline nm_Straight::StraightEquation geometry_cast<nm_Straight::StraightEquation>(nm_Vector::Vector v) {
	return geometry_cast<nm_Straight::StraightEquation>
		(geometry_cast<nm_Straight::p_Straight>(v));
}
*/

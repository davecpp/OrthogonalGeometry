#pragma once
#include "Point.h"
#include "Line.h"


using product_t = double;

class Vector {
	Point begin, end;
public:

	Vector(Point begin, Point end) : begin(begin), end(end) {}
	Vector(Point end) : begin(Point(0, 0)), end(end) {}

	//Point getBegin() { return begin; }
	//Point getEnd() { return end; }
	//void setBegin(Point p) { begin = p; }
	//void setEnd(Point p) { end = p; }

	coord_t getX() { return Point::delta_x(end, begin); };
	coord_t getY() { return Point::delta_y(end, begin); }


	//Vector Product
	NODISCARD static Vector CrossProduct(Vector v1, Vector v2);
	//Cross Product
	static Vector VectorProduct(Vector v1, Vector v2) {
		return CrossProduct(v1, v2);
	}


	//Scalar Product
	NODISCARD static product_t DotProduct(Vector v1, Vector v2);
	//Dot Product
	static product_t ScalarProduct(Vector v1, Vector v2) {
		return DotProduct(v1, v2);
	}

	//Vector product module
	NODISCARD static product_t PseudoScalarProduct(Vector v1, Vector v2);




};

/////////////////////////////////////////////////////////////
//////////////////IMPLEMENTATION///////////////////////////
/////////////////////////////////////////////////////////////

#include <boost/assert.hpp>
NODISCARD inline Vector Vector::CrossProduct(Vector v1, Vector v2)
{
	BOOST_ASSERT_MSG(false, "implementation");
	return v1;
}



NODISCARD inline product_t Vector::DotProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}

NODISCARD inline product_t Vector::PseudoScalarProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getY() - v2.getX() * v1.getY();
}


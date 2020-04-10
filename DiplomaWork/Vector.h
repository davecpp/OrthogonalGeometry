#pragma once
#include <cmath>
#include "Point.h"
#include "Line.h"
#include "Angles.h"

using product_t = double;


class Vector {
	Point begin, end;
public:

	explicit Vector(Point begin, Point end) : begin(begin), end(end) {}
	explicit Vector(Point end) : begin(Point(0, 0)), end(end) {}

	//Point getBegin() { return begin; }
	//Point getEnd() { return end; }
	//void setBegin(Point p) { begin = p; }
	//void setEnd(Point p) { end = p; }

private:
	coord_t getX() const { return Point::delta_x(end, begin); };
	coord_t getY() const { return Point::delta_y(end, begin); }
public:
	distance_t module() const { return Point::distance(begin, end); };

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
	//with radian
	NODISCARD static radian_t Angle_rad(Vector v1, Vector v2);
	//with degree
	NODISCARD static angle_t Angle(Vector v1, Vector v2);

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


//cross(vector) product module
NODISCARD inline product_t Vector::DotProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}
//dot product-> cross(vector) product module
NODISCARD inline product_t Vector::PseudoScalarProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getY() - v2.getX() * v1.getY();
}

//v1^v2 with radian
inline radian_t Vector::Angle_rad(Vector v1, Vector v2)
{
	//module(v1) * module(v2) * cos(a) = ScalarProduct(v1,v2)
	product_t s = ScalarProduct(v1, v2);
	//acos return [0,pi], if argument ![-1,1] -> throw domain error
	return radian_t(std::acos(s / (v1.module() * v2.module())));
}
//v1^v2 with degree
NODISCARD angle_t Vector::Angle(Vector v1, Vector v2)
{
	//radian * 180 / pi
	return toAngle(Angle_rad(v1, v2));
}


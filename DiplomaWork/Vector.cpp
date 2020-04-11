#include "Vector.h"
#include <boost/assert.hpp>

BEGIN_NAMESPACE(nm_Vector)
NODISCARD Vector Vector::CrossProduct(Vector v1, Vector v2)
{
	BOOST_ASSERT_MSG(false, "implementation");
	return v1;
}


//cross(vector) product module
NODISCARD product_t Vector::DotProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}
//dot product-> cross(vector) product module
NODISCARD product_t Vector::PseudoScalarProduct(Vector v1, Vector v2)
{
	return v1.getX() * v2.getY() - v2.getX() * v1.getY();
}

//v1^v2 with radian
NODISCARD radian_t Vector::Angle_rad(Vector v1, Vector v2)
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
END_NAMESPACE(nm_Vector)
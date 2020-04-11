#include "Angles.h"

BEGIN_NAMESPACE(nm_Angles)


NODISCARD bool angle_t::isSharp()
{
	return angle < (max() / 2);
}

NODISCARD bool angle_t::isObtuse()
{
	return angle > (max() / 2);
}


NODISCARD angle_t angle_t::SharpAngle(angle_t a)
{
	return a.isSharp() ? a : (angle_t::max() - a);
}

NODISCARD angle_t angle_t::ObtuseAngle(angle_t a)
{
	return a.isObtuse() ? a : (angle_t::max() - a);
}



NODISCARD bool radian_t::isSharp()
{
	return radian < (max() / 2);
}

NODISCARD bool radian_t::isObtuse()
{
	return radian > (max() / 2);
}

NODISCARD radian_t radian_t::SharpRadian(radian_t a)
{
	return a.isSharp() ? a : (radian_t::max() - a);
}

NODISCARD radian_t radian_t::ObtuseRadian(radian_t a)
{
	return a.isObtuse() ? a : (radian_t::max() - a);
}


angle_t operator-(angle_t l, angle_t r) {
	return angle_t(l.angle - r.angle);
}
angle_t operator+(angle_t l, angle_t r) {
	return angle_t(l.angle + r.angle);
}

radian_t operator-(radian_t l, radian_t r) {
	return radian_t(l.radian - r.radian);
}
radian_t operator+(radian_t l, radian_t r) {
	return radian_t(l.radian + r.radian);
}


//rad * 180 / pi
angle_t toAngle(radian_t rad) {
	return angle_t(rad.radian * 180 / radian_t::pi);
}
//angle * pi /180
radian_t toRadian(angle_t angle) {
	return radian_t(angle.angle * radian_t::pi / 180);
}

END_NAMESPACE(nm_Angles)


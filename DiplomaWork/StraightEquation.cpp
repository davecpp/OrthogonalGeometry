#include "StraightEquation.h"

BEGIN_NAMESPACE(nm_Straight)




StraightEquation StraightEquation::PerpendicularStraight(Point p) const
{
	//A(y-y1) - B(x-x1) = 0, => a = A, b = -B, c = B*x1 - A*y1
	return StraightEquation(a, -b, b * p.getX() - a / p.getY());
}

NODISCARD bool StraightEquation::ContainsPoint(Point p) const
{
	return (a * p.getX() + b * p.getY() + c) == 0;
}

NODISCARD distance_t StraightEquation::DistanceToPoint(Point p) const
{
	return Compute(p) / std::sqrt(square(a) + square(b));
}

NODISCARD Point StraightEquation::ProjectionPoint(Point p) const
{
	StraightEquation se = PerpendicularStraight(p);
	//se is always perpendicular this
	return IntersectionPoint(*this, se).value();
}

NODISCARD PointLineRelationship StraightEquation::PointRelation(Point p) const
{
	auto v = Compute(p);
	if (isVertical())
		return v * a > 0 ? PointLineRelationship::VerticalRight : PointLineRelationship::VerticalLeft;
	//p.getX() < -c / a ? PointLineRelationship::VerticalLeft : PointLineRelationship::VerticalRight;


	if (v > 0)
		return  PointLineRelationship::UpperHalfPlane;
	else if (v == 0)
		return PointLineRelationship::OnStraight;
	else /*v<0*/
		return  PointLineRelationship::LowerHalfPlane;
}

NODISCARD bool StraightEquation::isVertical() const
{
	return b == 0;
}

NODISCARD bool StraightEquation::isHorizontal() const
{
	return a == 0;
}

std::optional<Point> StraightEquation::IntersectionPoint(StraightEquation s1, StraightEquation s2)
{
	if (!areIntersect(s1, s2))
		return std::optional<Point>();

	coef_t d = s1.getA() * s2.getB() - s2.getA() * s1.getB();//a1*b2-a2*b1
	coef_t dx = s1.getC() * s2.getB() - s2.getC() * s1.getB();//c1*b2-c2*b1
	coef_t dy = s1.getA() * s2.getC() - s2.getA() * s1.getC();//a1*c2-a2*c1

	return Point(dx / d, dy / d);
}

bool StraightEquation::areParallel(StraightEquation s1, StraightEquation s2)
{
	//sin(0 || 180) = 0
	return Vector::PseudoScalarProduct(s1.guideVector(), s2.guideVector()) == 0;
}

bool StraightEquation::areIntersect(StraightEquation s1, StraightEquation s2)
{
	return !areParallel(s1, s2);
}

bool StraightEquation::arePerpendicular(StraightEquation s1, StraightEquation s2)
{
	//cos(90) = 0
	return Vector::ScalarProduct(s1.guideVector(), s2.guideVector()) == 0;
}

bool StraightEquation::areEqual(StraightEquation s1, StraightEquation s2)
{
	return s1.getA() == s2.getA() && s1.getB() == s2.getB() && s1.getC() == s2.getC();
}



angle_t StraightEquation::Angle(StraightEquation s1, StraightEquation s2)
{
	angle_t a = Vector::Angle(toVector(s1), toVector(s2));
	return angle_t::SharpAngle(a);
}

angle_t StraightEquation::ObtuseAngle(StraightEquation s1, StraightEquation s2)
{
	//return angle_t::ObtuseAngle(Angle(s1, s2));
	angle_t a = Vector::Angle(toVector(s1), toVector(s2));
	return angle_t::ObtuseAngle(a);
}

radian_t StraightEquation::Radian(StraightEquation s1, StraightEquation s2)
{
	radian_t a = Vector::Angle_rad(toVector(s1), toVector(s2));
	return radian_t::SharpRadian(a);
}

radian_t StraightEquation::ObtuseRadian(StraightEquation s1, StraightEquation s2)
{
	radian_t r = Vector::Angle_rad(toVector(s1), toVector(s2));
	return radian_t::ObtuseRadian(r);
}

END_NAMESPACE(nm_Straight)
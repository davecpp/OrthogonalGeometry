#include "Straight.h"


BEGIN_NAMESPACE(nm_Straight)


//Construct Vector from l
Vector Straight::toVector(Straight s) {
	return Vector(s.firstPoint(), s.secondPoint());
}



//return Intersection point
std::optional<Point> Straight::IntersectionPoint(Straight s1, Straight s2)
{
	//https://www.e-olymp.com/ru/blogs/posts/25
	if (!areIntersect(s1, s2))
		return std::optional<Point>();
	StraightEquation eq1 = s1.toEquation();
	StraightEquation eq2 = s2.toEquation();

	auto d = eq1.a * eq2.b - eq2.a * eq1.b;//a1*b2-a2*b1
	auto dx = eq1.c * eq2.b - eq2.c * eq1.b;//c1*b2-c2*b1
	auto dy = eq1.a * eq2.c - eq2.a * eq1.c;//a1*c2-a2*c1

	return Point(dx / d, dy / d);
}

//true-> l1 || l2, l1 and l2 parallel, if l1 == l2 return true
bool Straight::areParallel(Straight l1, Straight l2)
{
	//sin(0) = 0, Angle(l1,l2) = 0
	return Vector::PseudoScalarProduct(
		Vector(toVector(l1)),
		Vector(toVector(l2))
	) == 0;
}
//true-> s1 and s2 are intersect, if s1 == s2 return false
NODISCARD bool Straight::areIntersect(Straight s1, Straight s2)
{
	return !areParallel(s1, s2);
}
//true-> l1 || l2, l1 and l2 perpendicular, Angle(l1,l2) = 90 degree
bool Straight::arePerpendicular(Straight l1, Straight l2)
{
	//cos(90) = 0
	return Vector::ScalarProduct(toVector(l1), toVector(l2)) == 0;
}

//l1 and l2 belong in one straight
bool Straight::areEqual(Straight l1, Straight l2)
{
	return l1.ContainsPoint(l2.firstPoint()) && l1.ContainsPoint(l2.secondPoint());
}

//distance between Straight(l) and m
distance_t Straight::DistanceToPoint(Point m)
{
	//h * length = Area
	product_t S_Area = Vector::PseudoScalarProduct(
		Vector(p1, p2), Vector(p1, m));
	return S_Area / Point::distance(p1, p2);
}

//Point projection coordinate
Point Straight::ProjectionPoint(Point p)
{
	//https://rsdn.org/forum/alg/1655970.all

	coord_t delta_x = p2.getX() - p1.getX();
	coord_t delta_y = p2.getY() - p1.getY();
	auto fDenominator = square(delta_x) + square(delta_y);
	auto K = (delta_x * (p.getX() - p1.getX()) + delta_y * (p.getY() - p1.getY())) / fDenominator;
	return Point(p1.getX() + delta_x * K, p1.getY() + delta_y * K);
}

//Point and Line Relation
PointLineRelationship Straight::PointRelation(Point p) const
{

	const auto [p1, p2] = Point::minmax_X(this->p1, this->p2);
	product_t relation = Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, p));

	if (relation == 0)//OnStraight(p))
		return PointLineRelationship::OnStraight;

	//check the verticality only after OnStraight
	else if (isVertical()) {
		return p.getX() < p1.getX() ? PointLineRelationship::VerticalLeft
			: PointLineRelationship::VerticalRight;
	}
	else if (relation < 0)
		return PointLineRelationship::LowerHalfPlane;
	else /*relation > 0*/
		return PointLineRelationship::UpperHalfPlane;
}


//true-> Stright Vertical
NODISCARD bool Straight::isVertical() const
{
	return p1.getAbscis() == p2.getAbscis();
}
//true-> Straight Horizontal
NODISCARD bool Straight::isHorizontal() const
{
	return p1.getOrdinate() == p2.getOrdinate();
}

StraightEquation Straight::toEquation()
{
	//http://www.math.by/geometry/eqline.html
	StraightEquation eq;
	eq.a = Point::delta_y(p1, p2);
	eq.b = Point::delta_x(p2, p1);
	eq.c = p1.getX() * p2.getY() - p1.getY() * p2.getX();
	return eq;
}




//return l1^l2 sharp angle (result <= 90)
angle_t Straight::Angle(Straight l1, Straight l2)
{
	angle_t a = Vector::Angle(toVector(l1), toVector(l2));
	return angle_t::SharpAngle(a);
}
//return l1^l2 obtuse angle (result >= 90)
angle_t Straight::ObtuseAngle(Straight l1, Straight l2)
{
	//return angle_t::ObtuseAngle(Angle(l1, l2));
	angle_t a = Vector::Angle(toVector(l1), toVector(l2));
	return angle_t::ObtuseAngle(a);
}
//return l1^l2 sharp angle with radian (result <= pi/2)
radian_t Straight::Radian(Straight l1, Straight l2)
{
	radian_t r = Vector::Angle_rad(toVector(l1), toVector(l2));
	return radian_t::SharpRadian(r);
}
//return l1^l2 obtuse angle with radian (result >= pi/2)
radian_t Straight::ObtuseRadian(Straight l1, Straight l2)
{
	//return radian_t::ObtuseRadian(Radian(l1, l2));
	radian_t r = Vector::Angle_rad(toVector(l1), toVector(l2));
	return radian_t::ObtuseRadian(r);
}

//Straight l1 Contains point m
bool Straight::ContainsPoint(Point m)
{
	return Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, m)) == 0;
}

bool operator==(Straight l, Straight r)
{
	return Straight::areEqual(l, r);
}

bool operator!=(Straight l, Straight r)
{
	return !(l == r);
}

END_NAMESPACE(nm_Straight)
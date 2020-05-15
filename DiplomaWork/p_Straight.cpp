#include "Straight.h"
#include "p_Straight.h"



IN_NAEMSPACE_GEOMETRY(nm_Straight)


//Pack Vector from l
Vector p_Straight::toVector() const {
	return Vector(p1, p2);
}





//p_Straight l1 Contains point m
bool p_Straight::ContainsPoint(Point m) const
{
	return Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, m)) == 0;
}


//distance between p_Straight(l) and m
distance_t p_Straight::DistanceToPoint(Point m) const
{
	//h * length = Area
	product_t S_Area = Vector::PseudoScalarProduct(
		Vector(p1, p2), Vector(p1, m));
	return S_Area / Point::distance(p1, p2);
}

//Point projection coordinate
NODISCARD Point p_Straight::ProjectionPoint(Point m) const
{
	//https://rsdn.org/forum/alg/1655970.all

	coord_t delta_x = p2.getX() - p1.getX();
	coord_t delta_y = p2.getY() - p1.getY();
	auto fDenominator = square(delta_x) + square(delta_y);
	auto K = (delta_x * (m.getX() - p1.getX()) + delta_y * (m.getY() - p1.getY())) / fDenominator;
	return Point(p1.getX() + delta_x * K, p1.getY() + delta_y * K);
}

//Point and Line Relation
PointLineRelationship p_Straight::PointRelation(Point p) const
{

	const auto [m1, m2] = Point::minmax_X(this->p1, this->p2);
	product_t relation = Vector::PseudoScalarProduct(Vector(m1, m2), Vector(m1, p));

	if (relation == 0)//OnStraight(m))
		return PointLineRelationship::OnStraight;

	//check the verticality only after OnStraight
	else if (isVertical()) {
		return p.getX() < m1.getX() ? PointLineRelationship::VerticalLeft
			: PointLineRelationship::VerticalRight;
	}
	else if (relation < 0)
		return PointLineRelationship::LowerHalfPlane;
	else /*relation > 0*/
		return PointLineRelationship::UpperHalfPlane;
}


//true-> Stright Vertical
NODISCARD bool p_Straight::isVertical() const
{
	return p1.getAbscis() == p2.getAbscis();
}
//true-> p_Straight Horizontal
NODISCARD bool p_Straight::isHorizontal() const
{
	return p1.getOrdinate() == p2.getOrdinate();
}

std::optional<coord_t> p_Straight::appropriateX(coord_t y)
{
	if(isHorizontal()) return std::optional<coord_t>();
	return (y - p1.getY()) / (p2.getY() - p1.getY())/*K*/ * (p2.getX() - p1.getX()) + p1.getX();
}

std::optional<coord_t> p_Straight::appropriateY(coord_t x)
{
	if (isVertical()) std::optional<coord_t>();
	return (x - p1.getX()) / (p2.getX() - p1.getX())/*K*/ * (p2.getY() - p1.getY()) + p1.getY();
}




//return Intersection point
std::optional<Point> p_Straight::IntersectionPoint(p_Straight s1, p_Straight s2)
{
	//https://www.e-olymp.com/ru/blogs/posts/25
	if (!areIntersect(s1, s2))
		return std::optional<Point>();
	StraightEquation eq1 = geometry_cast<StraightEquation>(s1);
	StraightEquation eq2 = geometry_cast<StraightEquation>(s2);

	auto d = eq1.getA() * eq2.getB() - eq2.getA() * eq1.getB();//a1*b2-a2*b1
	auto dx = eq1.getC() * eq2.getB() - eq2.getC() * eq1.getB();//c1*b2-c2*b1
	auto dy = eq1.getA() * eq2.getC() - eq2.getA() * eq1.getC();//a1*c2-a2*c1

	return Point(dx / d, dy / d);

}

//true-> l1 || l2, l1 and l2 parallel, if l1 == l2 return true
bool p_Straight::areParallel(p_Straight l1, p_Straight l2)
{
	//sin(0) = 0, Angle(l1,l2) = 0
	return Vector::PseudoScalarProduct(
		Vector(l1.toVector()),
		Vector(l2.toVector())
	) == 0;
}
//true-> s1 and s2 are intersect, if s1 == s2 return false
NODISCARD bool p_Straight::areIntersect(p_Straight s1, p_Straight s2)
{
	return !areParallel(s1, s2);
}
//true-> l1 || l2, l1 and l2 perpendicular, Angle(l1,l2) = 90 degree
bool p_Straight::arePerpendicular(p_Straight l1, p_Straight l2)
{
	//cos(90) = 0
	return Vector::ScalarProduct(l1.toVector(), l2.toVector()) == 0;
}

//l1 and l2 belong in one straight
bool p_Straight::areEqual(p_Straight l1, p_Straight l2)
{
	return l1.ContainsPoint(l2.firstPoint()) && l1.ContainsPoint(l2.secondPoint());
}




//return l1^l2 sharp angle (result <= 90)
angle_t p_Straight::Angle(p_Straight l1, p_Straight l2)
{
	angle_t a = Vector::Angle(l1.toVector(), l2.toVector());
	return angle_t::SharpAngle(a);
}
//return l1^l2 obtuse angle (result >= 90)
angle_t p_Straight::ObtuseAngle(p_Straight l1, p_Straight l2)
{
	//return angle_t::ObtuseAngle(Angle(l1, l2));
	angle_t a = Vector::Angle(l1.toVector(), l2.toVector());
	return angle_t::ObtuseAngle(a);
}
//return l1^l2 sharp angle with radian (result <= pi/2)
radian_t p_Straight::Radian(p_Straight l1, p_Straight l2)
{
	radian_t r = Vector::Angle_rad(l1.toVector(), l2.toVector());
	return radian_t::SharpRadian(r);
}
//return l1^l2 obtuse angle with radian (result >= pi/2)
radian_t p_Straight::ObtuseRadian(p_Straight l1, p_Straight l2)
{
	//return radian_t::ObtuseRadian(Radian(l1, l2));
	radian_t r = Vector::Angle_rad(l1.toVector(), l2.toVector());
	return radian_t::ObtuseRadian(r);
}


bool operator==(p_Straight l, p_Straight r)
{
	return p_Straight::areEqual(l, r);
}

bool operator!=(p_Straight l, p_Straight r)
{
	return !(l == r);
}

END_NAMESPACE_GEOMETRY(nm_Straight)
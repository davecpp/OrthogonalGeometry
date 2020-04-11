#include <algorithm>
#include "Line.h"
#include "Vector.h"

BEGIN_NAMESPACE(nm_Line)
using namespace nm_Vector;


//Construct Vector from l
Vector toVector(Line l) {
	return Vector(l.firstPoint(), l.secondPoint());
}

//true -> l1 and l2 intersetced
LinesIntersection Line::IntersectionType(Line l1, Line l2)
{
	PointLineRelationship relation11 = l1.PointRelation(l2.firstPoint());
	PointLineRelationship relation12 = l1.PointRelation(l2.secondPoint());
	PointLineRelationship relation21 = l2.PointRelation(l1.firstPoint());
	PointLineRelationship relation22 = l2.PointRelation(l1.secondPoint());

	if (relation11 != relation12 && relation21 != relation22)
		return LinesIntersection::IntersectInPoint;
	//l1 and l2 belong in the one straight
	if (relation11 == relation12 && relation11 == PointLineRelationship::OnStraight) {
		BOOST_ASSERT_MSG(inOneStraight(l1, l2), "Implement error");
		if (l1.max_x() == l2.min_x() || l2.max_x() == l1.min_x()
			&& l1.max_y() == l2.min_y() || l2.max_y() == l1.min_y())
			return LinesIntersection::IntersectInPoint;

		else if ((l1.min_x() < l2.max_x() && l1.max_x() > l2.min_x())//conformity with x
			|| (l1.min_y() < l2.max_y() && l1.max_y() > l2.min_y()))// conformity with y
			return LinesIntersection::IntersectInLine;
		return LinesIntersection::NotIntersect;
	}
	return LinesIntersection::NotIntersect;
}



//two Lines Intersection Point
std::optional<Point> Line::IntersectionPoint(Line l1, Line l2)
{
	if (IntersectionType(l1, l2) != LinesIntersection::IntersectInPoint)
		return std::optional<Point>();

	product_t Z1 = Vector::PseudoScalarProduct(toVector(l1), Vector(l1.firstPoint(), l2.firstPoint()));
	product_t Z2 = Vector::PseudoScalarProduct(toVector(l1), Vector(l1.firstPoint(), l2.secondPoint()));
	if (Z1 == 0 && Z2 == 0) {
		if (l1.isEndPoint(l2.firstPoint())) return l2.firstPoint();
		else if (l1.isEndPoint(l2.secondPoint())) return l2.secondPoint();
	}
	return Point(
		l2.firstPoint().getX() + (l2.secondPoint().getX() - l2.firstPoint().getX()) * std::abs(Z1 / (Z2 - Z1)),
		l2.firstPoint().getY() + (l2.secondPoint().getY() - l2.firstPoint().getY()) * std::abs(Z1 / (Z2 - Z1))
	);
}


//true-> l1 || l2, l1 and l2 parallel, Angle(l1,l2) = 0
bool Line::areParallel(Line l1, Line l2)
{
	//sin(0) = 0
	return Vector::PseudoScalarProduct(
		Vector(toVector(l1)),
		Vector(toVector(l2))
	) == 0;
}
//true-> l1 || l2, l1 and l2 perpendicular, Angle(l1,l2) = 90 degree
bool Line::arePerpendicular(Line l1, Line l2)
{
	//cos(90) = 0
	return Vector::ScalarProduct(
		Vector(l1.firstPoint(), l1.secondPoint()),
		Vector(l2.firstPoint(), l2.secondPoint())
	) == 0;
}

//l1 and l2 belong in one straight
bool Line::inOneStraight(Line l1, Line l2)
{
	return l1.OnStraight(l2.firstPoint()) && l1.OnStraight(l2.secondPoint());
}

//distance between Straight(l) and p
distance_t Line::StraightPointDistance(Line l, Point p)
{
	//h * length = Area
	product_t S_Area = Vector::PseudoScalarProduct(
		Vector(toVector(l)), Vector(l.firstPoint(), p));
	return S_Area / l.length();
}

//return l1^l2 sharp angle (result <= 90)
angle_t Line::Angle(Line l1, Line l2)
{
	angle_t a = Vector::Angle(toVector(l1), toVector(l2));
	return angle_t::SharpAngle(a);
}
//return l1^l2 obtuse angle (result >= 90)
angle_t Line::ObtuseAngle(Line l1, Line l2)
{
	//return angle_t::ObtuseAngle(Angle(l1, l2));
	angle_t a = Vector::Angle(toVector(l1), toVector(l2));
	return angle_t::ObtuseAngle(a);
}
//return l1^l2 sharp angle with radian (result <= pi/2)
radian_t Line::Radian(Line l1, Line l2)
{
	radian_t r = Vector::Angle_rad(toVector(l1), toVector(l2));
	return radian_t::SharpRadian(r);
}
//return l1^l2 obtuse angle with radian (result >= pi/2)
radian_t Line::ObtuseRadian(Line l1, Line l2)
{
	//return radian_t::ObtuseRadian(Radian(l1, l2));
	radian_t r = Vector::Angle_rad(toVector(l1), toVector(l2));
	return radian_t::ObtuseRadian(r);
}



//true-> perpendicular falls on a segment, m has projection on Line
bool Line::HasProjection(Point m) const
{
	return Vector::ScalarProduct(Vector(p1, m), Vector(p1, p2)) < 0
		|| Vector::ScalarProduct(Vector(p2, m), Vector(p2, p1)) < 0;
}

//Line length, distance(p1,p2)
distance_t Line::length() const
{
	return Point::distance(p1, p2);
}

//return distance between Line and Point
distance_t Line::DistanceToPoint(Point m) const
{
	if (HasProjection(m)) {
		// h * length = Area
		product_t S_Area = std::abs(Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, m)));
		return S_Area / length();
	}
	else
		return std::min(Point::distance(p1, m), Point::distance(p2, m));
}

//true-> Line contains Point m
bool Line::ContainsPoint(Point m) const
{
	return  OnStraight(m) &&
		Vector::ScalarProduct(Vector(m, p1), Vector(m, p2)) <= 0;
}
//Do the Line Contains Point, if we know point relation, ContainsPoint optimized version
bool Line::ContainsPoint(Point m, PointLineRelationship relation) const
{
	if (relation == PointLineRelationship::OnStraight)
		return Vector::ScalarProduct(Vector(m, p1), Vector(m, p2)) <= 0;
	else return false;
}

//Point and Line Relation
PointLineRelationship Line::PointRelation(Point p) const
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

//true -> Point and Line on one straight
bool Line::OnStraight(Point p) const
{
	return Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, p)) == 0;
}

//true-> Line Vertical
bool Line::isVertical() const
{
	return p1.getAbscis() == p2.getAbscis();
}
//true-> Line Horizontal
bool Line::isHorizontal() const
{
	return p1.getOrdinate() == p2.getOrdinate();
}



Point Line::getLeftPoint() const
{
	return p1.getAbscis() < p2.getAbscis() ? p1 : p2;
}

Point Line::getRightPoint() const
{
	return p1.getAbscis() > p2.getAbscis() ? p1 : p2;
}

Point Line::getUpperPoint() const
{
	return p1.getOrdinate() > p2.getOrdinate() ? p1 : p2;
}

Point Line::getBottomPoint() const
{
	return p1.getOrdinate() < p2.getOrdinate() ? p1 : p2;
}



END_NAMESPACE(nm_Line)
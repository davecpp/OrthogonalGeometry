#include <algorithm>
#include "Line.h"
#include "Vector.h"


//true -> l1 and l2 intersetced
inline bool Line::areIntersect(Line l1, Line l2)
{
	PointLineRelationship relation1 = l1.PointRelation(l2.firstPoint());
	PointLineRelationship relation2 = l1.PointRelation(l2.secondPoint());
	if (relation1 != PointLineRelationship::OnStraight
		&& relation2 != PointLineRelationship::OnStraight)
		return relation1 != relation2;
	else//one of the endpoints l2 belongs to the l1 line straight
		return l1.ContainsPoint(l2.firstPoint()) || l1.ContainsPoint(l2.secondPoint());
}

//true-> l1 || l2, l1 and l2 parallel
bool Line::areParallel(Line l1, Line l2)
{
	return Vector::PseudoScalarProduct(
		Vector(l1.firstPoint(), l1.secondPoint()),
		Vector(l2.firstPoint(), l2.secondPoint())
	) == 0;
}

//true-> perpendicular falls on a segment, m has projection on Line
bool Line::HasProjection(Point m)
{
	return Vector::PseudoScalarProduct(Vector(p1, m), Vector(p1, p2)) < 0
		|| Vector::PseudoScalarProduct(Vector(p2, m), Vector(p2, p1)) < 0;
}

//Line length, distance(p1,p2)
distance_t Line::length()
{
	return Point::distance(p1, p2);
}

//return distance between Line and Point
distance_t Line::DistanceToPoint(Point m)
{
	if (HasProjection(m)) {
		// h * length = Area
		product_t S_Area = Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, m));
		return S_Area / length();
	}
	else
		return std::min(Point::distance(p1, m), Point::distance(p2, m));
}

//Line contains Point m
bool Line::ContainsPoint(Point m)
{
	return  OnStraight(m) &&
		Vector::ScalarProduct(Vector(m, p1), Vector(m, p2)) <= 0;
}

//Point and Line Relation
PointLineRelationship Line::PointRelation(Point p)
{
	if (OnStraight(p))//relation = 0
		return PointLineRelationship::OnStraight;

	//check the verticality only after OnStraight
	if (isVertical()) {
		return p.getX() < p1.getX() ? PointLineRelationship::VerticalLeft
			: PointLineRelationship::VerticalRight;
	}

	const auto [p1, p2] = Point::minmax_X(this->p1, this->p2);
	product_t relation = Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, p));

	if (relation < 0)
		return PointLineRelationship::LowerHalfPlane;
	else /*relation > 0*/
		return PointLineRelationship::UpperHalfPlane;
}

//true -> Point and Line on one straight
bool Line::OnStraight(Point p)
{
	return Vector::PseudoScalarProduct(Vector(p1, p2), Vector(p1, p)) == 0;
}

//true-> Line Vertical
bool Line::isVertical()
{
	return p1.getAbscis() == p2.getAbscis();
}
//true-> Line Horizontal
bool Line::isHorizontal()
{
	return p1.getOrdinate() == p2.getOrdinate();
}



Point Line::getLeftPoint()
{
	return p1.getAbscis() < p2.getAbscis() ? p1 : p2;
}

Point Line::getRightPoint()
{
	return p1.getAbscis() > p2.getAbscis() ? p1 : p2;
}

Point Line::getUpperPoint()
{
	return p1.getOrdinate() > p2.getOrdinate() ? p1 : p2;
}

Point Line::getBottomPoint()
{
	return p1.getOrdinate() < p2.getOrdinate() ? p1 : p2;
}



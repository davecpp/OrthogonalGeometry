#include <algorithm>
#include "Line.h"
#include "Vector.h"



BEGIN_NAMESPACE(nm_Line)
using namespace nm_Vector;



//true -> l1 and l2 intersetced
LinesIntersection Line::IntersectionType(Line l1, Line l2)
{
	//add in the future bounding box optimization, T.Kormen chapter 35, page 811

	PointLineRelationship relation11 = l1.PointRelation(l2.firstPoint());
	PointLineRelationship relation12 = l1.PointRelation(l2.secondPoint());
	PointLineRelationship relation21 = l2.PointRelation(l1.firstPoint());
	PointLineRelationship relation22 = l2.PointRelation(l1.secondPoint());

	if (relation11 != relation12 && relation21 != relation22)
		return LinesIntersection::IntersectInPoint;
	//l1 and l2 belong in the one straight
	if (relation11 == relation12 && relation11 == PointLineRelationship::OnStraight) {
		BOOST_ASSERT_MSG(l1.OnStraight(l2.firstPoint()) && l1.OnStraight(l2.secondPoint()), "Implement error");

		if (l1.max_x() == l2.min_x() || l2.max_x() == l1.min_x()
			&& l1.max_y() == l2.min_y() || l2.max_y() == l1.min_y())
			return LinesIntersection::Continues;

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
	//https://habr.com/ru/post/267037/

	LinesIntersection intersect = IntersectionType(l1, l2);
	if (intersect == LinesIntersection::IntersectInPoint) {
		product_t Z1 = Vector::PseudoScalarProduct(l1.toVector(), Vector(l1.firstPoint(), l2.firstPoint()));
		product_t Z2 = Vector::PseudoScalarProduct(l1.toVector(), Vector(l1.firstPoint(), l2.secondPoint()));
		auto K = std::abs(Z1 / (Z2 - Z1));
		return Point(
			l2.firstPoint().getX() + (l2.secondPoint().getX() - l2.firstPoint().getX()) * K,
			l2.firstPoint().getY() + (l2.secondPoint().getY() - l2.firstPoint().getY()) * K
		);
	}
	else if (intersect == LinesIntersection::Continues) {
		if (l1.isEndPoint(l2.firstPoint())) return l2.firstPoint();
		else if (l1.isEndPoint(l2.secondPoint())) return l2.secondPoint();
	}
	return std::optional<Point>();

}

//true-> perpendicular falls on a segment, m has projection on Line
bool Line::HasProjection(Point m) const
{
	// degree(m,p1,p2) > 90 => scalar({p1,m},{p1,p2}) < 0 || 
	// degree(m,p2,p1) > 90 => scalar({p2,m},{p2,p1}) < 0 //cos(obtuse) < 0
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
	return toPStraight().PointRelation(p);
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
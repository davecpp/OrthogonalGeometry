#pragma once
#include <cstdint>
#include <optional>
#include "Point.h"
#include "Angles.h"
#include "Straight.h"

#include "Vector.h"


BEGIN_NAMESPACE(nm_Line)
using namespace nm_Point;
using namespace nm_Angles;
using namespace nm_Straight;

class Line;


enum class LinesIntersection :std::uint8_t {
	NotIntersect,

	IntersectInPoint,
	PointIntersection = IntersectInPoint,

	Continues,//OnStraight && Intersect in one point

	IntersectInLine,
	LineIntersection = IntersectInLine
};

class Line
{
	const Point p1, p2;
public:
	explicit Line(Point p1, Point p2) :p1(p1), p2(p2) {
		BOOST_ASSERT_MSG(p1 != p2, "invalid line");
	}
	explicit Line(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :Line(Point(x1, y1), Point(x2, y2)) {}
	explicit Line(Point p1, coord_t x2, coord_t y2) :Line(p1, Point(x2, y2)) {}
	explicit Line(coord_t x1, coord_t y1, Point p2) :Line(Point(x1, y1), p2) {}

	//static methods///////////////////

	//do two Line's intersect
	NODISCARD static LinesIntersection IntersectionType(Line, Line);
	//two Lines Intersection Point
	NODISCARD static std::optional<Point> IntersectionPoint(Line, Line);
	//two lines intersection if l1 is vertical
	NODISCARD static std::optional<Point> VerticalLineIntersection(Line vertical, Line);
	//two lines intersection if l1 is horizontal
	NODISCARD static std::optional<Point> HorizontalLineIntersection(Line horizontal, Line);


	//Point has projection on Line
	NODISCARD bool HasProjection(Point) const;
	//Line length, distance between p1 and p2
	NODISCARD distance_t length() const;
	//Distance Between Line and Point
	NODISCARD distance_t DistanceToPoint(Point) const;
	//Do the Line Contains Point 
	NODISCARD bool ContainsPoint(Point) const;
	//Do the Line Contains Point, if we know point relation, ContainsPoint optimized version
	NODISCARD bool ContainsPoint(Point, PointLineRelationship) const;
	//relation Point and Line
	NODISCARD PointLineRelationship PointRelation(Point) const;
	//Point and Line in one p_Straight
	NODISCARD bool OnStraight(Point) const;


	//Construct Vector from l
	NODISCARD Vector toVector() const {
		return Vector(p1, p2);
	}
	//Construct p_Straight from l
	NODISCARD p_Straight toPStraight() const {
		return p_Straight(p1, p2);
	}


	//is the Line Vertical
	bool isVertical() const;
	//is the Line Horizontal
	bool isHorizontal() const;

	NODISCARD std::optional<coord_t> appropriateX(coord_t Y);
	NODISCARD std::optional<coord_t> appropriateY(coord_t X);


	bool isEndPoint(Point p) const { return p == p1 || p == p2; }

	Point firstPoint() const { return p1; }
	Point secondPoint() const { return p2; }

	coord_t x1() const { return p1.getX(); }
	coord_t x2() const { return p2.getX(); }
	coord_t y1() const { return p1.getY(); }
	coord_t y2() const { return p2.getY(); }

	coord_t max_x() const { return x1() > x2() ? x1() : x2(); }
	coord_t max_y() const { return y1() > y2() ? y1() : y2(); }

	coord_t min_x() const { return x1() < x2() ? x1() : x2(); }
	coord_t min_y() const { return y1() < y2() ? y1() : y2(); }

	coord_t delta_x() const { return Point::delta_x(p1, p2); }
	coord_t delta_y() const { return Point::delta_y(p1, p2); }




	Point getLeftPoint() const;
	Point getRightPoint() const;
	Point getUpperPoint() const;
	Point getBottomPoint() const;
};




struct range {
	const coord_t min, max;
	explicit range(coord_t a, coord_t b) :
		min(a < b ? a : b),
		max(a > b ? a : b)
	{
		BOOST_ASSERT_MSG(a != b, "invalid range");
	}

	NODISCARD static std::optional<range> IntersectionRange(range r1, range r2) {
		coord_t ret_min = std::max(r1.min, r2.min);
		coord_t ret_max = std::min(r1.max, r2.max);
		if (ret_min < ret_max)
			return range(ret_min, ret_max);
		return std::optional<range>();
	}

	NODISCARD static std::optional<range> range_X(Line l1, Line l2) {
		if (l1.isVertical() || l2.isVertical())
			return std::optional<range>();
		range r1 = range(l1.firstPoint().getX(), l1.secondPoint().getX());
		range r2 = range(l2.firstPoint().getX(), l2.secondPoint().getX());
		return IntersectionRange(r1, r2);
	}

	NODISCARD static std::optional<range> range_Y(Line l1, Line l2) {
		if (l1.isHorizontal() || l2.isHorizontal())
			return std::optional<range>();
		range r1 = range(l1.firstPoint().getY(), l1.secondPoint().getY());
		range r2 = range(l2.firstPoint().getY(), l2.secondPoint().getY());
		return IntersectionRange(r1, r2);
	}
};


END_NAMESPACE(nm_Line)


//template<>
//inline nm_Vector::Vector geometry_cast<nm_Vector::Vector>(nm_Line::Line l) {
//	return l.toVector();
//}

template<>
inline nm_Straight::p_Straight geometry_cast<nm_Straight::p_Straight>(nm_Line::Line l) {
	return l.toPStraight();
}

template<>
inline nm_Straight::StraightEquation geometry_cast<nm_Straight::StraightEquation>(nm_Line::Line l) {
	return geometry_cast<nm_Straight::StraightEquation>(l.toPStraight());
}




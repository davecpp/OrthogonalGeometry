#pragma once
#include <cstdint>
#include <optional>
#include "Point.h"
#include "Angles.h"

BEGIN_NAMESPACE(nm_Line)
using namespace nm_Point;
using namespace nm_Angles;

enum class PointLineRelationship : std::uint8_t
{
	Undefined = 0,
	LowerHalfPlane = 1,
	OnStraight,
	UpperHalfPlane,

	VerticalLeft,
	VerticalRight,
};

enum class LinesIntersection :std::uint8_t {
	NotIntersect,

	IntersectInPoint,
	PointIntersection = IntersectInPoint,

	IntersectInLine,
	LineIntersection = IntersectInLine
};

class Line
{
	Point p1, p2;
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
	//do two Line's parallel Angle(l1,l2) = 0
	NODISCARD static bool areParallel(Line, Line);
	//do two Line's perpendicular Angle(l1,l2) = 90 degree
	NODISCARD static bool arePerpendicular(Line, Line);
	//two Lines belong in one straight
	NODISCARD static bool inOneStraight(Line, Line);
	//distance Straight(line) to Point
	NODISCARD static distance_t StraightPointDistance(Line, Point);
	//tow Lines  sharp angle with degree (result <= 90)
	NODISCARD static angle_t Angle(Line, Line);
	//two Lines obtuse angle with degree (result >= 90)
	NODISCARD static angle_t ObtuseAngle(Line, Line);

	//tow Lines  sharp angle with radian (result <= pi/2)
	NODISCARD static radian_t Radian(Line, Line);
	//two Lines obtuse angle with radian (result >= 90)
	NODISCARD static radian_t ObtuseRadian(Line, Line);
	//////////////////////////////////

	//Point has projection on Line
	NODISCARD bool HasProjection(Point) const;
	//Line length, distance between p1 and p2
	NODISCARD distance_t length() const;
	//does the point belong to Line
	//Distance Between Line and Point
	NODISCARD distance_t DistanceToPoint(Point) const;
	//Do the Line Contains Point 
	NODISCARD bool ContainsPoint(Point) const;
	//Do the Line Contains Point, if we know point relation, ContainsPoint optimized version
	NODISCARD bool ContainsPoint(Point, PointLineRelationship) const;
	//relation Point and Line
	NODISCARD PointLineRelationship PointRelation(Point) const;
	//Point and Line in one Straight
	NODISCARD bool OnStraight(Point) const;



	//is the Line Vertical
	bool isVertical() const;
	//is the Line Horizontal
	bool isHorizontal() const;


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

	bool isEndPoint(Point p) const { return p == p1 || p == p2; }

	coord_t delta_x() const { return Point::delta_x(p1, p2); }
	coord_t delta_y() const { return Point::delta_y(p1, p2); }


	Point getLeftPoint() const;
	Point getRightPoint() const;
	Point getUpperPoint() const;
	Point getBottomPoint() const;
};


END_NAMESPACE(nm_Line)
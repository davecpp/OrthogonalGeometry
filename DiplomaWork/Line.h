#pragma once
#include <cstdint>
#include "Point.h"

enum class PointLineRelationship : std::uint8_t
{
	LowerHalfPlane = 1,
	OnStraight,
	UpperHalfPlane,

	Undefined = 0,
	VerticalLeft,
	VerticalRight,
	/*LinVerticalPointLeft,
	LineVerticalPointRight,*/
};

class Line
{
	Point p1, p2;
public:
	Line(Point p1, Point p2) :p1(p1), p2(p2) {}
	Line(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :p1(x1, y1), p2(x2, y2) {}
	Line(Point p1, coord_t x2, coord_t y2) :p1(p1), p2(x2, y2) {}
	Line(coord_t x1, coord_t y1, Point p2) :p1(x1, y1), p2(p2) {}

	//static methods///////////////////

	//do two Line's intersect
	NODISCARD static bool areIntersect(Line, Line);
	//do two Line's parallel
	NODISCARD static bool areParallel(Line, Line);
	//////////////////////////////////

	//Point has projection on Line
	NODISCARD bool HasProjection(Point);

	NODISCARD distance_t length();
	//does the point belong to Line

	NODISCARD distance_t DistanceToPoint(Point);

	NODISCARD bool ContainsPoint(Point p);

	//relation Point and Line
	NODISCARD PointLineRelationship PointRelation(Point);

	NODISCARD bool OnStraight(Point);


	//is the Line Vertical
	bool isVertical();
	//is the Line Horizontal
	bool isHorizontal();


	Point firstPoint() { return p1; }
	Point secondPoint() { return p2; }

	Point getLeftPoint();
	Point getRightPoint();
	Point getUpperPoint();
	Point getBottomPoint();
};



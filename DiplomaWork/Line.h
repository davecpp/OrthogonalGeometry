#pragma once
#include <cstdint>
#include "Point.h"
#include "Angles.h"

enum class PointLineRelationship : std::uint8_t
{
	LowerHalfPlane = 1,
	OnStraight,
	UpperHalfPlane,

	Undefined = 0,
	VerticalLeft,
	VerticalRight,
};

class Line
{
	Point p1, p2;
public:
	explicit Line(Point p1, Point p2) :p1(p1), p2(p2) {}
	explicit Line(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :p1(x1, y1), p2(x2, y2) {}
	explicit Line(Point p1, coord_t x2, coord_t y2) :p1(p1), p2(x2, y2) {}
	explicit Line(coord_t x1, coord_t y1, Point p2) :p1(x1, y1), p2(p2) {}

	//static methods///////////////////

	//do two Line's intersect
	NODISCARD static bool areIntersect(Line, Line);
	//do two Line's parallel
	NODISCARD static bool areParallel(Line, Line);
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

	Point getLeftPoint() const;
	Point getRightPoint() const;
	Point getUpperPoint() const;
	Point getBottomPoint() const;
};



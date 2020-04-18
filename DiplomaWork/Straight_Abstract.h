#pragma once

#pragma once
#include <optional>
#include "Point.h"
#include "Angles.h"



IN_NAEMSPACE_GEOMETRY(nm_Straight)
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


class Straight {
public:



	//Point and Line in one p_Straight
	virtual bool ContainsPoint(Point) const = 0;
	//distance p_Straight(line) to Point
	virtual distance_t DistanceToPoint(Point) const = 0;
	//Point projection in p_Straight
	virtual Point ProjectionPoint(Point) const = 0;
	//relation Point and Line
	virtual PointLineRelationship PointRelation(Point) const = 0;

	// true->p_Straight Vertical
	virtual bool isVertical() const = 0;
	//true->p_Straight Horizontal
	virtual bool isHorizontal() const = 0;



/*
	//two Straights intersection point
	NODISCARD static std::optional<Point> IntersectionPoint(p_Straight, p_Straight);
	//do two Line's parallel Angle(l1,l2) = 0
	NODISCARD static bool areParallel(p_Straight, p_Straight);
	//do two Line's is intersect Angle(l1,l2) != 0
	NODISCARD static bool areIntersect(p_Straight, p_Straight);
	//do two Line's perpendicular Angle(l1,l2) = 90 degree
	NODISCARD static bool arePerpendicular(p_Straight, p_Straight);
	//two Lines belong in one straight
	NODISCARD static bool areEqual(p_Straight, p_Straight);


	//two Lines  sharp angle with degree (result <= 90)
	NODISCARD static angle_t Angle(p_Straight, p_Straight);
	//two Lines obtuse angle with degree (result >= 90)
	NODISCARD static angle_t ObtuseAngle(p_Straight, p_Straight);
	//tow Lines  sharp angle with radian (result <= pi/2)
	NODISCARD static radian_t Radian(p_Straight, p_Straight);
	//two Lines obtuse angle with radian (result >= 90)
	NODISCARD static radian_t ObtuseRadian(p_Straight, p_Straight);*/

};



END_NAMESPACE_GEOMETRY(nm_Straight)

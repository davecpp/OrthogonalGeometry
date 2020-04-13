#pragma once
#include <optional>
//#include "Line.h"
#include "Point.h"
#include "Angles.h"
#include "Vector.h"


BEGIN_NAMESPACE(nm_Straight)
using namespace nm_Vector;

enum class PointLineRelationship : std::uint8_t
{
	Undefined = 0,
	LowerHalfPlane = 1,
	OnStraight,
	UpperHalfPlane,

	VerticalLeft,
	VerticalRight,
};


struct StraightEquation {
	using coef_t = double;

	coef_t a, b, c;
};


class Straight {
	Point p1;
	Point p2;
	Point firstPoint() const { return p1; }
	Point secondPoint() const { return p2; }
	static Vector toVector(Straight s);

	//distance_t Denominator() { return square(Point::delta_x(p2,p1)) + square(Point::delta_y(p2,p1)); }

public:
	explicit Straight(Point p1, Point p2) :p1(p1), p2(p2) {
		BOOST_ASSERT_MSG(p1 != p2, "invalid line");
	}
	explicit Straight(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :Straight(Point(x1, y1), Point(x2, y2)) {}
	explicit Straight(Point p1, coord_t x2, coord_t y2) :Straight(p1, Point(x2, y2)) {}
	explicit Straight(coord_t x1, coord_t y1, Point p2) :Straight(Point(x1, y1), p2) {}
	//explicit Straight(Line l) : Straight(l.firstPoint(), l.secondPoint()) {}


	//Point and Line in one Straight
	NODISCARD bool ContainsPoint(Point);
	//distance Straight(line) to Point
	NODISCARD distance_t DistanceToPoint(Point);
	//Point projection in Straight
	NODISCARD Point ProjectionPoint(Point);
	//relation Point and Line
	NODISCARD PointLineRelationship PointRelation(Point) const;

	// true->Straight Vertical
	NODISCARD bool isVertical() const;
	//true->Straight Horizontal
	NODISCARD bool isHorizontal() const;

	//Straight to Straight equation` ax + by + c
	NODISCARD StraightEquation toEquation();


	//two Straights intersection point
	NODISCARD static std::optional<Point> IntersectionPoint(Straight, Straight);
	//do two Line's parallel Angle(l1,l2) = 0
	NODISCARD static bool areParallel(Straight, Straight);
	//do two Line's is intersect Angle(l1,l2) != 0
	NODISCARD static bool areIntersect(Straight, Straight);
	//do two Line's perpendicular Angle(l1,l2) = 90 degree
	NODISCARD static bool arePerpendicular(Straight, Straight);
	//two Lines belong in one straight
	NODISCARD static bool areEqual(Straight, Straight);


	//two Lines  sharp angle with degree (result <= 90)
	NODISCARD static angle_t Angle(Straight, Straight);
	//two Lines obtuse angle with degree (result >= 90)
	NODISCARD static angle_t ObtuseAngle(Straight, Straight);
	//tow Lines  sharp angle with radian (result <= pi/2)
	NODISCARD static radian_t Radian(Straight, Straight);
	//two Lines obtuse angle with radian (result >= 90)
	NODISCARD static radian_t ObtuseRadian(Straight, Straight);


};

inline bool operator==(Straight l, Straight r);
inline bool operator!=(Straight l, Straight r);

END_NAMESPACE(nm_Straight)
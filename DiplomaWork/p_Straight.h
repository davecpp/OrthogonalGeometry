#pragma once
#include <optional>
#include "Straight_Abstract.h"
#include "Point.h"
#include "Angles.h"
#include "Vector.h"


BEGIN_NAMESPACE(nm_Straight)
using namespace nm_Vector;

class StraightEquation;

class p_Straight :public Straight {
	const Point p1;
	const Point p2;
public:

	explicit p_Straight(Point p1, Point p2) :p1(p1), p2(p2) {
		BOOST_ASSERT_MSG(p1 != p2, "invalid line");
	}
	explicit p_Straight(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :p_Straight(Point(x1, y1), Point(x2, y2)) {}
	explicit p_Straight(Point p1, coord_t x2, coord_t y2) :p_Straight(p1, Point(x2, y2)) {}
	explicit p_Straight(coord_t x1, coord_t y1, Point p2) :p_Straight(Point(x1, y1), p2) {}
	//explicit p_Straight(Line l) : p_Straight(l.firstPoint(), l.secondPoint()) {}

	Point firstPoint() const { return p1; }
	Point secondPoint() const { return p2; }


	//Point and Line in one p_Straight
	NODISCARD bool ContainsPoint(Point) const override;
	//distance p_Straight(line) to Point
	NODISCARD distance_t DistanceToPoint(Point) const override;
	//Point projection in p_Straight
	NODISCARD Point ProjectionPoint(Point) const override;
	//relation Point and Line
	NODISCARD PointLineRelationship PointRelation(Point) const override;

	// true->p_Straight Vertical
	NODISCARD bool isVertical() const override;
	//true->p_Straight Horizontal
	NODISCARD bool isHorizontal() const override;

	//get Y(X) = Y, return X
	NODISCARD std::optional<coord_t> appropriateX(coord_t y);
	//get Y(X)
	NODISCARD std::optional<coord_t> appropriateY(coord_t x);

	//guide vector for Straight
	NODISCARD Vector toVector() const;




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
	NODISCARD static radian_t ObtuseRadian(p_Straight, p_Straight);


};

inline bool operator==(p_Straight l, p_Straight r);
inline bool operator!=(p_Straight l, p_Straight r);

END_NAMESPACE(nm_Straight)




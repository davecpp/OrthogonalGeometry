#pragma once
#include "Straight_Abstract.h"
#include "Vector.h"


BEGIN_NAMESPACE(nm_Straight)
using namespace nm_Vector;
class p_Straight;

class StraightEquation :public Straight {
	using coef_t = double;

	coef_t a, b, c;

	//ax + by + c
	auto Compute(Point p) const {
		return a * p.getX() + b * p.getY() + c;
	}



public:
	explicit StraightEquation(coord_t a, coord_t b, coord_t c) :a(a), b(b), c(c) {
		BOOST_ASSERT_MSG(!(a == 0 && b == 0), "invalid Straight Equation");
	}

	//ax + by + c = 0
	std::optional<coord_t> getY(coord_t x) const {
		if (b == 0) return std::optional<coord_t>();
		return (-c - a * x) / b;
	}
	//ax + by + c = 0
	std::optional<coord_t> getX(coord_t y) const {
		if (a == 0) return std::optional<coord_t>();
		return (-c - b * y) / a;
	}
	//ax + by + c = 0
	std::optional<coord_t> appropriateY(coord_t x) const {
		return getY(x);
	}
	//ax + by + c = 0
	std::optional<coord_t> appropriateX(coord_t y) const {
		return getX(y);
	}


	NODISCARD coef_t getA() const { return a; }
	NODISCARD coef_t getB() const { return b; }
	NODISCARD coef_t getC() const { return c; }

	static Vector toVector(StraightEquation s) { return s.guideVector(); }
	Vector guideVector() const { return Vector(-b, a); }
	Vector normalVecto() const { return Vector(a, b); }


	NODISCARD StraightEquation PerpendicularStraight(Point) const;

	NODISCARD bool ContainsPoint(Point) const override;

	NODISCARD distance_t DistanceToPoint(Point) const override;


	NODISCARD Point ProjectionPoint(Point) const override;

	NODISCARD PointLineRelationship PointRelation(Point) const override;

	NODISCARD bool isVertical() const override;


	NODISCARD bool isHorizontal() const override;




	//two Straights intersection point
	NODISCARD static std::optional<Point> IntersectionPoint(StraightEquation, StraightEquation);
	//do two Line's parallel Angle(l1,l2) = 0
	NODISCARD static bool areParallel(StraightEquation, StraightEquation);
	//do two Line's is intersect Angle(l1,l2) != 0
	NODISCARD static bool areIntersect(StraightEquation, StraightEquation);
	//do two Line's perpendicular Angle(l1,l2) = 90 degree
	NODISCARD static bool arePerpendicular(StraightEquation, StraightEquation);
	//two Lines belong in one straight
	NODISCARD static bool areEqual(StraightEquation, StraightEquation);

	//two Lines  sharp angle with degree (result <= 90)
	NODISCARD static angle_t Angle(StraightEquation, StraightEquation);
	//two Lines obtuse angle with degree (result >= 90)
	NODISCARD static angle_t ObtuseAngle(StraightEquation, StraightEquation);
	//tow Lines  sharp angle with radian (result <= pi/2)
	NODISCARD static radian_t Radian(StraightEquation, StraightEquation);
	//two Lines obtuse angle with radian (result >= 90)
	NODISCARD static radian_t ObtuseRadian(StraightEquation, StraightEquation);
};

inline bool operator==(StraightEquation l, StraightEquation r) {
	return StraightEquation::areEqual(l, r);
}
inline bool operator!=(StraightEquation l, StraightEquation r) {
	return !(l == r);
}

END_NAMESPACE(nm_Straight)

#include <iostream>
#include <optional>

#include "Point.h"
#include "Vector.h"
#include "Line.h"
#include "Rectangle.h"
#include "BadCoordinate.h"
#include "p_Straight.h"
#include "StraightEquation.h"
#include "RectanglesSet.h"
#include "BOOST_REGISTRATION.h"

using namespace geometry;
using namespace nm_Point;
using namespace nm_Vector;
using namespace nm_Angles;
using namespace nm_Line;
using namespace nm_Straight;
using namespace nm_Rectangle;


int main() {
	Line l1(Point(0, 0), Point(0.5, 0));
	Line l2(Point(0.000000001, 0.001), Point(0.0000000003, -0.0000009));

	p_Straight s1(0, 0, 10, 0);
	p_Straight s2(5, 3, 5, 5);

	std::cout << p_Straight::IntersectionPoint(s1, s2).value().getX() << "," << p_Straight::IntersectionPoint(s1, s2).value().getY() << std::endl;

	//Point point(15, 0);

	//std::cout << s1.ProjectionPoint(point).getX() << "," << s1.ProjectionPoint(point).getY() << std::endl;



	auto p = Line::IntersectionPoint(l1, l2);
	if (p.has_value())
		std::cout << p.value().getX() << "," << p.value().getY() << std::endl;
	else
		std::cout << "Points are not intersect, or intersect in line" << std::endl;


	//std::cout << Line::areParallel(l1, l2) << std::endl;
	std::cout << l1.DistanceToPoint(Point(10, 10)) << std::endl;
	std::cout << l1.ContainsPoint(Point(0, 5)) << std::endl;

}
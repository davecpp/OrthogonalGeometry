#include <iostream>
#include <optional>

#include "Point.h"
#include "Vector.h"
#include "Line.h"
#include "Rectangle.h"
#include "BadCoordinate.h"

using namespace nm_Point;
using namespace nm_Vector;
using namespace nm_Angles;
using namespace nm_Line;
using namespace nm_Rectangle;


int main() {
	Line l1(Point(0, 0), Point(10, 10));
	Line l2(Point(10, 10), Point(15, 15));



	auto p = Line::IntersectionPoint(l1, l2);
	if (p.has_value())
		std::cout << p.value().getX() << "," << p.value().getY() << std::endl;
	else
		std::cout << "Points are not intersect, or intersect in line" << std::endl;


	std::cout << Line::areParallel(l1, l2) << std::endl;
	std::cout << l1.DistanceToPoint(Point(10, 10)) << std::endl;
	std::cout << l1.ContainsPoint(Point(0, 5)) << std::endl;

}
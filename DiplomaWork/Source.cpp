#include <iostream>
#include <optional>

#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
#include "BadCoordinate.h"


int main() {

	Line l1(Point(0, 0), Point(0, 10));
	Line l2(Point(5, 5), Point(5, -5));

	std::cout << Line::areIntersect(l1, l2) << std::endl;
	std::cout << Line::areParallel(l1, l2) << std::endl;
	std::cout << l1.DistanceToPoint(Point(10, 10)) << std::endl;
	std::cout << l1.ContainsPoint(Point(0, 5)) << std::endl;

}
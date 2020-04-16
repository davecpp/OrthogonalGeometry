#pragma once
#include "Point.h"
#include "Line.h"
#include "Straight.h"

using area_t = decltype(distance_t()* distance_t());

BEGIN_NAMESPACE(nm_Rectangle)
using namespace nm_Point;
using namespace nm_Line;



class Rectangle
{
	Point lb, ru;

public:
	explicit Rectangle(coord_t x1, coord_t y1, coord_t x2, coord_t y2);
	explicit Rectangle(Point l1, Point l2);
	explicit Rectangle(Line l);

	Line getLeftSide() const;
	Line getRightSide() const;
	Line getBottomSide() const;
	Line getUpperSide() const;


	Point LeftBottom() const;
	Point LeftUpper() const;
	Point RightBottom() const;
	Point RightUpper() const;

	coord_t min_X() const { return lb.getX(); }
	coord_t max_X() const { return ru.getX(); }
	coord_t min_Y() const { return lb.getY(); }
	coord_t max_Y() const { return ru.getY(); }

	coord_t left_X() const { return min_X(); }
	coord_t right_X() const { return max_X(); }
	coord_t bottom_Y() const { return min_Y(); }
	coord_t upper_Y() const { return max_Y(); }

	distance_t width() const;
	distance_t height() const;

	area_t Area() const;
	distance_t Perimetr() const;

	NODISCARD bool ContainsPoint(Point) const;
	NODISCARD bool ContainsLine(Line) const;
	NODISCARD bool areIntersect(Line) const;
	NODISCARD std::optional<Line> commonLine(Line) const;

	//Do are intersect two Rectangles
	NODISCARD static bool areIntersect(Rectangle, Rectangle);
	//Do are two Rectangle Intersect in Rec
	NODISCARD static bool areIntersectInRect(Rectangle, Rectangle);
	//two Rectangle Intersection Rectangle
	NODISCARD static std::optional<Rectangle> IntersectionRect(Rectangle, Rectangle);
};


struct VerticalSide {
	coord_t x;
	range y;

	explicit VerticalSide(Line l) :
		x(l.firstPoint().getX()),
		y(l.firstPoint().getY(), l.secondPoint().getY()) 
	{
		BOOST_ASSERT_MSG(l.isVertical(),"the line is not vertical");
	}
};


END_NAMESPACE(nm_Rectangle)
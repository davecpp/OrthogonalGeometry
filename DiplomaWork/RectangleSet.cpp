#include "RectanglesSet.h"




IN_NAEMSPACE_GEOMETRY(nm_Set_Of_Rectangles)

using return_type = RectangleSet::return_type;//vector<index>
using point = boost_point;
using line = boost_line;
using rectangle = boost_rectangle;
using polygon = boost_polygon;



constexpr double reserve_coef = 0.07;
#define Construct_Return_type(expr) return_type expr; expr.reserve(rects.size() * reserve_coef);


return_type RectangleSet::Intersects(Point p) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Intersects(Line l) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(line(l))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Intersects(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Intersects(Polygon poly) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(poly)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}



return_type RectangleSet::Contains(Point p) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::contains(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Contains(Line l) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::contains(point(l.firstPoint())) && bgi::contains(point(l.secondPoint())))
		; it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Contains(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::contains(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}



return_type RectangleSet::Covers(Point p) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::covers(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Covers(Line l) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::covers(point(l.firstPoint())) && bgi::covers(point(l.secondPoint())))
		; it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Covers(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::covers(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}





return_type RectangleSet::Overlaps(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::overlaps(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Overlaps(Line l) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(line(l))); it != tree.qend(); ++it) {
		if (!bg::within(point(l.firstPoint()), it->first) || !bg::within(point(l.secondPoint()), it->first))
			ret.push_back(it->second);
	}
	return ret;
}




return_type RectangleSet::CoveredBy(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::covered_by(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}




return_type RectangleSet::Disjoint(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::disjoint(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}



return_type RectangleSet::Within(Rectangle r) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::within(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}






return_type RectangleSet::Nearest(Point p, size_t K) const
{
	Construct_Return_type(ret)
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::nearest(point(p), K)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Nearest(Line l, size_t K) const
{
	Construct_Return_type(ret)
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::nearest(line(l), K)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Nearest(Rectangle r, size_t K) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::nearest(rectangle(r), K)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}







return_type RectangleSet::euclideanDistance(Point p, distance_t d) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::nearest(point(p), rects.size())); it != tree.qend(); ++it) {
		if (bg::distance(point(p), it->first) <= d)
			ret.push_back(it->second);
		else break;
	}
	return ret;
}

return_type RectangleSet::euclideanDistance(Line l, distance_t d) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::nearest(line(l), rects.size())); it != tree.qend(); ++it) {
		if (bg::distance(line(l), it->first) <= d)
			ret.push_back(it->second);
		else break;
	}
	return ret;
}

return_type RectangleSet::euclideanDistance(Rectangle r, distance_t d) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::nearest(rectangle(r), rects.size())); it != tree.qend(); ++it) {
		if (bg::distance(rectangle(r), it->first) <= d)
			ret.push_back(it->second);
		else break;
	}
	return ret;
}

return_type RectangleSet::euclideanDistance(Polygon poly, distance_t d) const
{
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::nearest(poly, rects.size())); it != tree.qend(); ++it) {
		if (bg::distance(poly, it->first) <= d)
			ret.push_back(it->second);
		else break;
	}
	return ret;
}




return_type RectangleSet::fastDistance(Point p, distance_t d) const
{
	point ex_left_bottom(p.getX() - d / 2, p.getY() - d / 2);//if d > 0
	point ex_right_upper(p.getX() + d / 2, p.getY() + d / 2);
	rectangle extended_r(ex_left_bottom, ex_right_upper);

	//Intersected with extended_r
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(extended_r)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;

}

return_type RectangleSet::fastDistance(Line l, distance_t d) const
{
	l.ExtendLine(d);
	//https://stackoverflow.com/questions/1936934/turn-a-line-into-a-rectangle
	distance_t dx = l.delta_x();
	distance_t dy = l.delta_y();
	distance_t length = l.length();

	dx /= length;
	dy /= length;

	auto px = -dy * d / 2;
	auto py = dx * d / 2;
	coord_t x1 = l.firstPoint().getX(), x2 = l.secondPoint().getX();
	coord_t y1 = l.firstPoint().getY(), y2 = l.secondPoint().getY();
	polygon p{
		point{x1 + px,y1 + py},
		point{x2 + px,y2 + py},
		point{x2 - px,y2 - py},
		point{x1 - px,y1 - py},
		//closing polygon
		point{x1 + px,y1 + py}
	};


	//Intersected with extended_r
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(p)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::fastDistance(Rectangle r, distance_t d) const
{
	point ex_left_bottom(r.left_X() - d, r.bottom_Y() - d);
	point ex_right_upper(r.left_X() + d, r.bottom_Y() + d);
	rectangle extended_r(ex_left_bottom, ex_right_upper);

	//Intersect with extended_r
	Construct_Return_type(ret)
	for (auto it = tree.qbegin(bgi::intersects(extended_r)); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}













END_NAMESPACE_GEOMETRY(nm_Set_Of_Rectangles)



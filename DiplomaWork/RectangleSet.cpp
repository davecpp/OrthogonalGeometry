#include "RectanglesSet.h"


IN_NAEMSPACE_GEOMETRY(nm_Set_Of_Rectangles)

using return_type = RectangleSet::return_type;//vector<index>
using point = boost_point;
using line = boost_line;
using rectangle = boost_rectangle;





return_type RectangleSet::Intersects(Point p) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::intersects(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Intersects(Line l) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::intersects(line(l))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Intersects(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::intersects(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}



return_type RectangleSet::Contains(Point p) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::contains(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Contains(Line l) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::contains(point(l.firstPoint())) && bgi::contains(point(l.secondPoint())))
		; it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Contains(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::contains(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}



return_type RectangleSet::Covers(Point p) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::covers(point(p))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Covers(Line l) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::covers(point(l.firstPoint())) && bgi::covers(point(l.secondPoint())))
		; it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::Covers(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::covers(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}





return_type RectangleSet::Overlaps(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::overlaps(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

return_type RectangleSet::CoveredBy(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::covered_by(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}




return_type RectangleSet::Disjoint(Rectangle r) const
{
	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::disjoint(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}







return_type RectangleSet::Within(Rectangle r) const
{

	return_type ret;
	ret.reserve(rects.size() * 0.07);
	for (auto it = tree.qbegin(bgi::within(rectangle(r))); it != tree.qend(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}











END_NAMESPACE_GEOMETRY(nm_Set_Of_Rectangles)



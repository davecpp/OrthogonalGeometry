#pragma once
#include <vector>
#include <utility>//std::pair

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

//
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/polygon.hpp>

//Query Algorithms
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>



#include <boost/geometry/algorithms/distance.hpp>
//////////////////





#include "Point.h"
#include "Line.h"
#include "Rectangle.h"

BEGIN_GEOMETRY
namespace bgi = bg::index;
END_GEOMETRY

IN_NAEMSPACE_GEOMETRY(nm_Set_Of_Rectangles)
using namespace nm_Point;
using namespace nm_Line;
using namespace nm_Rectangle;


template<typename geometry_t>
using rtree = bgi::rtree<geometry_t, bgi::rstar<16>>;


class RectangleSet {
public:
	using RectArray = std::vector<Rectangle>;
	using BoostRectArray = std::vector<boost_rectangle>;
	using index_t = RectArray::size_type;
	using pair_t = std::pair<boost_rectangle, size_t>;
	using rtree = rtree<pair_t>;
	using return_type = std::vector<index_t>;

	const RectArray rects;
	const rtree tree;

	RectangleSet(RectArray&& rect_arr) : rects(std::move(rect_arr)), tree(toIndexVector()) {
		BOOST_ASSERT_MSG(!rects.empty(), "no input rectangles");
	}
	RectangleSet(BoostRectArray&& rect_arr) : rects(rect_arr.begin(), rect_arr.end()), tree(toIndexVector()) {
		BOOST_ASSERT_MSG(!rects.empty(), "no input rectangles");
	}


	void foo() {
		std::vector<pair_t> arr;
		boost_point p1(1, 2), p2(3, 4);
		boost_line l(p1, p2);
		boost_rectangle r(p1, p2);

		//tree.qbegin(bgi::intersects(boost_rectangle(r)));
		tree.query(bgi::contains(p1), std::back_inserter(arr));
		tree.query(bgi::intersects(l), std::back_inserter(arr));
		tree.query(bgi::covers(r), std::back_inserter(arr));
		
		//tree.query(bgi::covers(l), std::back_inserter(arr));

	}


	NODISCARD return_type Intersects(Point) const;
	NODISCARD return_type Intersects(Line) const;
	NODISCARD return_type Intersects(Rectangle) const;

	NODISCARD return_type Contains(Point) const;
	NODISCARD return_type Contains(Line) const;
	NODISCARD return_type Contains(Rectangle) const;

	NODISCARD return_type Covers(Point) const;
	NODISCARD return_type Covers(Line) const;
	NODISCARD return_type Covers(Rectangle) const;



	NODISCARD return_type Overlaps(Rectangle) const;

	NODISCARD return_type CoveredBy(Rectangle) const;

	NODISCARD return_type Disjoint(Rectangle) const;

	NODISCARD return_type Within(Rectangle) const;











private:
	NODISCARD std::vector<pair_t> toIndexVector() const {
		BOOST_ASSERT_MSG(!rects.empty(), "no input rectangles");
		std::vector<pair_t> ret;
		ret.reserve(rects.size());
		index_t i = 0;
		for (const auto& it : rects)
		{
			ret.emplace_back(it, i++);
		}
		return ret;
	}

};


END_NAMESPACE_GEOMETRY(nm_Set_Of_Rectangles)

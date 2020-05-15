#pragma once
#include <vector>
#include <utility>//std::pair

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/ring.hpp>

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


#include <unordered_set>


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


using boost_polygon = bg::model::ring<boost_point>;
using Polygon = boost_polygon;



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


	using iterator = RectArray::iterator;

	RectArray rects;
	rtree tree;

	RectangleSet(RectArray&& rect_arr) : rects(std::move(rect_arr)), tree(Pack()) {
	}
	RectangleSet(BoostRectArray&& rect_arr) : rects(rect_arr.begin(), rect_arr.end()), tree(Pack()) {
	}


	void foo() {
		std::vector<pair_t> arr;
		boost_point p1(1, 2), p2(3, 4);
		boost_line l(p1, p2);
		boost_rectangle r(p1, p2);

		boost_polygon poly;
		tree.query(bgi::nearest(poly, 2), std::back_inserter(arr));

		//tree.qbegin(bgi::intersects(boost_rectangle(r)));
		tree.query(bgi::contains(p1), std::back_inserter(arr));
		tree.query(bgi::intersects(l), std::back_inserter(arr));
		tree.query(bgi::covers(r), std::back_inserter(arr));

		//tree.query(bgi::covers(l), std::back_inserter(arr));

	}


	NODISCARD return_type Intersects(Point) const;
	NODISCARD return_type Intersects(Line) const;
	NODISCARD return_type Intersects(Rectangle) const;
	NODISCARD return_type Intersects(Polygon) const;


	NODISCARD return_type Contains(Point) const;
	NODISCARD return_type Contains(Line) const;
	NODISCARD return_type Contains(Rectangle) const;

	NODISCARD return_type Covers(Point) const;
	NODISCARD return_type Covers(Line) const;
	NODISCARD return_type Covers(Rectangle) const;



	NODISCARD return_type Overlaps(Rectangle) const;
	NODISCARD return_type Overlaps(Line) const;

	NODISCARD return_type CoveredBy(Rectangle) const;

	NODISCARD return_type Disjoint(Rectangle) const;

	NODISCARD return_type Within(Rectangle) const;


	NODISCARD return_type Nearest(Point, size_t) const;
	NODISCARD return_type Nearest(Line, size_t) const;
	NODISCARD return_type Nearest(Rectangle, size_t) const;


	NODISCARD return_type euclideanDistance(Point, distance_t) const;
	NODISCARD return_type euclideanDistance(Line, distance_t) const;
	NODISCARD return_type euclideanDistance(Rectangle, distance_t) const;
	NODISCARD return_type euclideanDistance(Polygon, distance_t) const;


	NODISCARD return_type fastDistance(Point, distance_t) const;
	NODISCARD return_type fastDistance(Line, distance_t) const;
	NODISCARD return_type fastDistance(Rectangle, distance_t) const;









	decltype(auto) begin() { return rects.begin(); }
	decltype(auto) end() { return rects.end(); }
	decltype(auto) operator[](const RectArray::size_type i) { return rects[i]; }
	void push_back(Rectangle r) { rects.push_back(r); tree.insert(create_pair(r)); }
	void add(Rectangle r) { push_back(r); }
	void remove(Rectangle r) { rects.erase(std::remove(rects.begin(), rects.end(), r)); tree.remove(create_pair(r)); }
	RectArray::size_type size() { return rects.size(); }



	template<typename Predicates, typename OutIter>
	rtree::size_type query(Predicates const& predicates, OutIter out_it) { return tree.query(predicates, out_it); }

	template<typename Predicates>
	rtree::const_query_iterator qbegin(Predicates const& predicates) { return tree.qbegin(predicates); }

	rtree::const_query_iterator qend() { return tree.qend(); }


private:

	/*struct simpleLess {
		bool operator()(const Rectangle& r1, const Rectangle& r2) const {
			for (size_t i = 0; i < 4; i++)
			{
				if (get(r1, i) < get(r2, i)) return true;
				else if (get(r1, i) == get(r2, i)) continue;
				else return false;
			}
			return false;
		}
	private:
		static coord_t get(const Rectangle& r, size_t i) {
			switch (i) {
			case 0:
				return r.min_X();
			case 1:
				return r.min_Y();
			case 2:
				return r.max_X();
			case 3:
				return r.max_Y();
			default:
				assert(false);
			}
		}
	};*/

	struct simpleHash {
		using argument_type = Rectangle;
		using result_type = size_t;

		result_type operator()(const argument_type& r) const noexcept {
			result_type hash = 0;
			for (size_t i = 0; i < 4; i++)
			{
				hash += (73 * hash + static_cast<result_type>(get(r, i))) % 9;
			}
			return hash;
		}
	private:
		static coord_t get(const Rectangle& r, size_t i) {
			switch (i) {
			case 0:
				return r.min_X();
			case 1:
				return r.min_Y();
			case 2:
				return r.max_X();
			case 3:
				return r.max_Y();
			default:
				assert(false);
			}
		}
	};

	NODISCARD std::vector<pair_t> Pack() {//for packing algorithm
		std::vector<pair_t> ret;
		ret.reserve(rects.size());
		index_t i = 0;

		//std::sort(rects.begin(), rects.end(), simpleLess()); //work in O(n*log(n))
		//rects.erase(std::unique(rects.begin(), rects.end()), rects.end());

		//duplicates remove work in O(n)
		std::unordered_set<Rectangle, simpleHash> s;
		auto end = std::remove_if(rects.begin(), rects.end(),
			[&s](const Rectangle& r) {return !s.insert(r).second; });
		rects.erase(end, rects.end());

		for (const auto& it : rects)
		{
			ret.emplace_back(it, i++);
		}
		return ret;
	}

	pair_t create_pair(Rectangle r) {
		return pair_t(boost_rectangle(r), rects.size() - 1);
	}
};


END_NAMESPACE_GEOMETRY(nm_Set_Of_Rectangles)

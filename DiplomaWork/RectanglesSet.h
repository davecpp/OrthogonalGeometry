#pragma once
#include <vector>
#include <map>
#include "Rectangle.h"
#include "Line.h"
//#include <set>


namespace std {
	template<>
	struct less <nm_Rectangle::VerticalSide>
	{
		using first_argument_type = nm_Rectangle::VerticalSide;
		using second_argument_type = nm_Rectangle::VerticalSide;
		using result_type = bool;

		bool operator()(const first_argument_type& l, const second_argument_type& r) const {
			return l.x < r.x;
		}

	};
}

BEGIN_NAMESPACE(nm_Set_Of_Rectangles)
using namespace nm_Rectangle;
using namespace nm_Line;



class RectanglesSet {
	std::vector<Rectangle> rects;
	using index_t = decltype(rects)::size_type;
	std::map<const VerticalSide, const index_t> sidemap;

	explicit RectanglesSet(std::vector<Rectangle>&& v) :
		rects(std::move(v))
	{
		for (decltype(rects)::size_type i = 0; i < rects.size(); i++)
		{
			sidemap.insert(std::make_pair(rects[i].getLeftSide(), i));
			sidemap.insert(std::make_pair(rects[i].getRightSide(), i));
		}
	}

	bool areOpener(VerticalSide v, index_t i) {
		return v.x == rects[i].min_X();
	}
	bool areCloser(VerticalSide v, index_t i) {
		return v.x == rects[i].max_X();
	}

	std::vector<std::pair<index_t, index_t>> IntersecteionPairs() {

		std::vector<std::pair<index_t, index_t>> ret;
		std::map<const VerticalSide, const index_t> currents;

		for (const auto& it : sidemap)
		{
			if (areCloser(it.first, it.second))
			{
				currents.erase(it.first);
				continue;
			}
			else
				BOOST_ASSERT_MSG(areOpener(it.first, it.second), "maybe opener or closer");
			//is opener

			for (const auto& v : currents)
			{
				if (VerticalSide::areIntersectY(v.first, it.first))
					ret.emplace_back(v.second, it.second);
			}

			currents.insert(it);
		}
		return ret;
	}


	std::vector<Rectangle> IntersectionRects() {
		std::vector<Rectangle> ret;
		auto rect_pairs = IntersecteionPairs();
		for (const auto& pairs : rect_pairs)
		{
			auto intersect = Rectangle::IntersectionRect(rects[pairs.first], rects[pairs.second]);
			BOOST_ASSERT_MSG(intersect.has_value(), "IMPL ERROR, ->first and second does not intersect");
			ret.push_back(intersect.value());
		}
		return ret;
	}



};


END_NAMESPACE(nm_Set_Of_Rectangles)

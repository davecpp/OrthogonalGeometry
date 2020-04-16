#pragma once
#include <vector>
#include <map>
#include "Rectangle.h"
#include "Line.h"


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
		//VerticalSide s(Line(0, 0, 0, 10));
		

	}



};


END_NAMESPACE(nm_Set_Of_Rectangles)

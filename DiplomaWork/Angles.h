#pragma once
#include <boost/math/constants/constants.hpp>
#include <boost/assert.hpp>
#include "Defines.h"

BEGIN_NAMESPACE(nm_Angles)
struct angle_t;
struct radian_t;

angle_t operator-(angle_t, angle_t);
angle_t operator+(angle_t, angle_t);
radian_t operator-(radian_t, radian_t);
angle_t operator+(angle_t, angle_t);

angle_t toAngle(radian_t rad);
radian_t toRadian(angle_t angle);


struct angle_t {
	using value_type = double;
	value_type angle;
	explicit angle_t(value_type angle) :angle(angle) {
		BOOST_ASSERT_MSG(angle >= 0 && angle <= 180, "invalid angle");
	}

	operator value_type() {
		BOOST_ASSERT_MSG(angle >= 0 && angle <= 180, "invalid angle");
		return angle;
	}
	//180 degree
	NODISCARD static angle_t max() {
		return angle_t(180);
	}
	//0 degree
	NODISCARD static angle_t min() {
		return angle_t(0);
	}
	
	//angle < 90
	NODISCARD bool isSharp();
	//angle > 90
	NODISCARD bool isObtuse();
	//sharp angle
	NODISCARD static angle_t SharpAngle(angle_t a);
	//obtuse angle
	NODISCARD static angle_t ObtuseAngle(angle_t a);
};


struct radian_t {
	using value_type = double;
	value_type radian;
	static constexpr value_type pi = boost::math::constants::pi<value_type>();
	explicit radian_t(value_type radian) :radian(radian) {
		BOOST_ASSERT_MSG(radian >= 0 && radian <= pi, "invalid radian");
	}

	operator value_type() {
		BOOST_ASSERT_MSG(radian >= 0 && radian <= pi, "invalid radian");
		return radian;
	}

	//pi radian
	NODISCARD static radian_t max() {
		return radian_t(pi);
	}
	//0 radian
	NODISCARD static radian_t min() {
		return radian_t(0);
	}

	//true-> radian < pi/2
	NODISCARD bool isSharp();
	//true-> radian >p/2
	NODISCARD bool isObtuse();
	//sharp angle with radian
	NODISCARD static radian_t SharpRadian(radian_t a);
	//obtuse angle with radian
	NODISCARD static radian_t ObtuseRadian(radian_t a);

};

END_NAMESPACE(nm_Angles)

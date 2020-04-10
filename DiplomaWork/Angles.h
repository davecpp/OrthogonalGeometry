#pragma once
#include <boost/math/constants/constants.hpp>
#include <boost/assert.hpp>
#include "Defines.h"

namespace {
	struct angle_t;
	struct radian_t;

	angle_t operator-(angle_t, angle_t);
	angle_t operator+(angle_t, angle_t);
	radian_t operator-(radian_t, radian_t);
	angle_t operator+(angle_t, angle_t);


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
		//angle < 90
		NODISCARD bool isSharp() {
			return angle < (max() / 2);
		}
		//angle > 90
		NODISCARD bool isObtuse() {
			return angle > (max() / 2);
		}
		//180 degree
		NODISCARD static angle_t max() {
			return angle_t(180);
		}
		//0 degree
		NODISCARD static angle_t min() {
			return angle_t(0);
		}
		//sharp angle
		NODISCARD static angle_t SharpAngle(angle_t a) {
			return a.isSharp() ? a : (angle_t::max() - a);
		}
		//obtuse angle
		NODISCARD static angle_t ObtuseAngle(angle_t a) {
			return a.isObtuse() ? a : (angle_t::max() - a);
		}
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
		//true-> radian < pi/2
		NODISCARD bool isSharp() {
			return radian < (max() / 2);
		}
		//true-> radian >p/2
		NODISCARD bool isObtuse() {
			return radian > (max() / 2);
		}
		//pi radian
		NODISCARD static radian_t max() {
			return radian_t(pi);
		}
		//0 radian
		NODISCARD static radian_t min() {
			return radian_t(0);
		}

		//sharp angle with radian
		NODISCARD static radian_t SharpRadian(radian_t a) {
			return a.isSharp() ? a : (radian_t::max() - a);
		}
		//obtuse angle with radian
		NODISCARD static radian_t ObtuseRadian(radian_t a) {
			return a.isObtuse() ? a : (radian_t::max() - a);
		}

	};

	inline angle_t operator-(angle_t l, angle_t r) {
		return angle_t(l.angle - r.angle);
	}
	inline angle_t operator+(angle_t l, angle_t r) {
		return angle_t(l.angle + r.angle);
	}


	inline radian_t operator-(radian_t l, radian_t r) {
		return radian_t(l.radian - r.radian);
	}
	inline radian_t operator+(radian_t l, radian_t r) {
		return radian_t(l.radian + r.radian);
	}
	//rad * 180 / pi
	angle_t toAngle(radian_t rad) {
		return angle_t(rad.radian * 180 / radian_t::pi);
	}
	//angle * pi /180
	radian_t toRadian(angle_t angle) {
		return radian_t(angle.angle * radian_t::pi / 180);
	}

}



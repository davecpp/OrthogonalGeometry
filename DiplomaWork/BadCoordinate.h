#pragma once
#include <exception>
#include "Defines.h"

class BadCoordinate :public std::exception {
protected:
	using msg = const char*;
	msg message;
public:
	//BadCoordinate() noexcept :message(nullptr) {}
	explicit BadCoordinate(msg message) noexcept :message(message) {}

	NODISCARD msg what() const noexcept override {
		return message;
	}
};


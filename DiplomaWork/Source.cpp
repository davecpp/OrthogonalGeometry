#include <iostream>
#include <optional>

#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
#include "BadCoordinate.h"


int main() {
	

	std::cout << std::numeric_limits<double>::min() << std::endl;
	std::cout << std::numeric_limits<double>::lowest() << std::endl;
	
	try {
		std::optional<double> value = std::nullopt;


		if (value.has_value()) {
			std::cout << value.has_value() << std::endl;
		}
		std::cout << value.value();
	}
	catch (const std::bad_optional_access& ex) {
		std::cout << ex.what();
	}

}
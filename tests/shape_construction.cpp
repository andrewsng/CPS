#include "catch.hpp"
#include "Shape.hpp"

TEST_CASE("Rectangle ctor requires correct input"){

	REQUIRE_THROWS_AS([&]() { Rectangle r(-5, 12); }(), std::invalid_argument);

}
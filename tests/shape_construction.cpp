#include "catch.hpp"
#include "Shape.hpp"

TEST_CASE("Rectangle ctor requires correct input"){

	REQUIRE_THROWS_AS([&]() { Rectangle r(-5, 12); }(), std::invalid_argument);

}

TEST_CASE("Square ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { Square s(-17.3); }(), std::invalid_argument);

}

TEST_CASE("Circle ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { Circle c(-21.7); }(), std::invalid_argument);

}
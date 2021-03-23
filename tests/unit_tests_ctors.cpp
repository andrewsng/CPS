#include "catch.hpp"
#include "Shape.hpp"

TEST_CASE("RectangleShape ctor requires correct input"){

	REQUIRE_THROWS_AS([&]() { RectangleShape r(-5, 12); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { RectangleShape r(5, -12); }(), std::invalid_argument);
}

TEST_CASE("SquareShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { SquareShape s(-17.3); }(), std::invalid_argument);
}

TEST_CASE("Circle ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { Circle c(-21.7); }(), std::invalid_argument);
}

TEST_CASE("TriangleShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { TriangleShape t(-48.12); }(), std::invalid_argument);
}

TEST_CASE("PolygonShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { PolygonShape p(-3, 25.9); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { PolygonShape p(8, -57.7); }(), std::invalid_argument);
}

TEST_CASE("SpacerShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { SpacerShape s(-151.2, 132.3); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { SpacerShape s(151.2, -132.3); }(), std::invalid_argument);
}
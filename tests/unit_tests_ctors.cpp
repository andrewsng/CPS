#include "catch.hpp"
#include "Shape.hpp"

TEST_CASE("RectangleShape ctor requires correct input"){

	REQUIRE_THROWS_AS([&]() { RectangleShape r(-5, 12); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { RectangleShape r(5, -12); }(), std::invalid_argument);
}

TEST_CASE("SquareShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { SquareShape s(-17.3); }(), std::invalid_argument);
}

TEST_CASE("CircleShape ctor requires correct input") {

	REQUIRE_THROWS_AS([&]() { CircleShape c(-21.7); }(), std::invalid_argument);
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

TEST_CASE("PlusShape ctor requires correct input") {
	REQUIRE_THROWS_AS([&]() { PlusShape f(-40, 40); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { PlusShape f(40, -40); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { PlusShape f(-40, -40); }(), std::invalid_argument);
}

TEST_CASE("SierpinskiShape ctor requires correct input") {
	REQUIRE_THROWS_AS([&]() { SierpinskiShape f(-39.52, 3); }(), std::invalid_argument);
	REQUIRE_THROWS_AS([&]() { SierpinskiShape f(39.52, -3); }(), std::invalid_argument);
}
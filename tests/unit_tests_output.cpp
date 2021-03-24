#include <string>
#include "catch.hpp"
#include "Shape.hpp"

int Number_Substring_Occurences(const std::string& input, const std::string& sub)
{
	// nice example of naive implementation based on discussion here
	// https://stackoverflow.com/questions/22489073/counting-the-number-of-occurrences-of-a-string-within-a-string

	size_t current_position = 0;
	int num_substrings = 0;

	while ((current_position = input.find(sub, current_position)) != std::string::npos) {
		num_substrings++;
		current_position += sub.length();
	}

	return num_substrings;
}

TEST_CASE("RectangleShape output generates correct number of lines") {

	RectangleShape r(47, 52);
	std::string r_out = r.ToPostScript();

	REQUIRE(Number_Substring_Occurences(r_out, "rlineto") == 3);
	REQUIRE(Number_Substring_Occurences(r_out, "closepath") == 1);
}

TEST_CASE("RectangleShape width and height") {
	
	RectangleShape r(47, 52);

	REQUIRE(r.Width() == Approx(47.0));
	REQUIRE(r.Height() == Approx(52.0));
}

TEST_CASE("PolygonShape output generates correct number of lines") {

	int num_sides = 17;
	PolygonShape p(num_sides, 37.5);
	std::string p_out = p.ToPostScript();

	REQUIRE(Number_Substring_Occurences(p_out, "rlineto") == num_sides - 1);
	REQUIRE(Number_Substring_Occurences(p_out, "closepath") == 1);
}

TEST_CASE("PolygonShape width and height") {

	const double e = 31.6;

	SECTION("n is odd") {
		const int n = 7;
		PolygonShape p(n, e);
		const double w = (e*sin(PI*(n-1)/(2*n)))/(sin(PI/n));
		const double h = e*(1+cos(PI/n))/(2*sin(PI/n));
		REQUIRE(p.Width() == Approx(w));
		REQUIRE(p.Height() == Approx(h));
	}
	SECTION("n is divisible by 4") {
		const int n = 8;
		PolygonShape p(n, e);
		const double w = e*cos(PI/n)/(sin(PI/n));
		const double h = w;
		REQUIRE(p.Width() == Approx(w));
		REQUIRE(p.Height() == Approx(h));
	}
	SECTION("n is divisible by 2, but not by 4") {
		const int n = 6;
		PolygonShape p(n, e);
		const double w = e/(sin(PI/n));
		const double h = e*cos(PI/n)/(sin(PI/n));
		REQUIRE(p.Width() == Approx(w));
		REQUIRE(p.Height() == Approx(h));
	}
}

TEST_CASE("SquareShape output generates correct number of lines") {

	SquareShape s(155.0);
	std::string s_out = s.ToPostScript();

	REQUIRE(Number_Substring_Occurences(s_out, "rlineto") == 3);
	REQUIRE(Number_Substring_Occurences(s_out, "closepath") == 1);
}

TEST_CASE("SquareShape width and height") {

	SquareShape s(235.63);

	REQUIRE(s.Width() == Approx(235.63));
	REQUIRE(s.Height() == Approx(235.63));
}

TEST_CASE("TriangleShape output generates correct number of lines") {

	TriangleShape t(92);
	std::string t_out = t.ToPostScript();

	REQUIRE(Number_Substring_Occurences(t_out, "rlineto") == 2);
	REQUIRE(Number_Substring_Occurences(t_out, "closepath") == 1);
}

TEST_CASE("TriangleShape width and height") {

	TriangleShape t1(235.63);
	REQUIRE(t1.Width() == Approx(235.63));
	REQUIRE(t1.Height() == Approx(204.0615659));
	TriangleShape t2(1.0);
	REQUIRE(t2.Width() == Approx(1.0));
	REQUIRE(t2.Height() == Approx(sqrt(3.0)/2.0));
}

TEST_CASE("CircleShape output generates correct number of lines") {

	CircleShape c(57);
	std::string c_out = c.ToPostScript();

	REQUIRE(Number_Substring_Occurences(c_out, "arc") == 1);
	REQUIRE(Number_Substring_Occurences(c_out, "closepath") == 1);
}

TEST_CASE("CircleShape width and height") {

	CircleShape c(118.49);
	REQUIRE(c.Width() == Approx(236.98));
	REQUIRE(c.Height() == Approx(236.98));
}

TEST_CASE("SpacerShape output generates correct number of lines") {

	SpacerShape s(155, 223);
	std::string s_out = s.ToPostScript();

	REQUIRE(Number_Substring_Occurences(s_out, "rlineto") == 0);
	REQUIRE(Number_Substring_Occurences(s_out, "closepath") == 0);
}
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


TEST_CASE("Polygon output generates correct number of lines") {

	int num_sides = 17;
	Polygon p(num_sides, 37.5);
	std::string p_out = p.ToPostScript();

	REQUIRE(Number_Substring_Occurences(p_out, "rlineto") == num_sides - 1);
	REQUIRE(Number_Substring_Occurences(p_out, "closepath") == 1);
}

TEST_CASE("Square output generates correct number of lines") {

	Square s(155.0);
	std::string s_out = s.ToPostScript();

	REQUIRE(Number_Substring_Occurences(s_out, "rlineto") == 3);
	REQUIRE(Number_Substring_Occurences(s_out, "closepath") == 1);
}


TEST_CASE("Triangle output generates correct number of lines") {

	Triangle t(92);
	std::string t_out = t.ToPostScript();

	REQUIRE(Number_Substring_Occurences(t_out, "rlineto") == 2);
	REQUIRE(Number_Substring_Occurences(t_out, "closepath") == 1);
}


TEST_CASE("Circle output generates correct number of lines") {

	Circle c(57);
	std::string c_out = c.ToPostScript();

	REQUIRE(Number_Substring_Occurences(c_out, "arc") == 1);
	REQUIRE(Number_Substring_Occurences(c_out, "closepath") == 1);
}


TEST_CASE("Spacer output generates correct number of lines") {

	Spacer s(155, 223);
	std::string s_out = s.ToPostScript();

	REQUIRE(Number_Substring_Occurences(s_out, "rlineto") == 0);
	REQUIRE(Number_Substring_Occurences(s_out, "closepath") == 0);
}
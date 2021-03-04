//
// Created by Chris Hartman on 2/10/21.
//
#include "catch.hpp"
#include "Expression.hpp"
using std::make_unique;

auto makeNumber(int num) {
   return make_unique<NumberExpression>(num);
}

TEST_CASE("Expressions") {
   auto e13 = make_unique<NumberExpression>(13);
   REQUIRE(e13->evaluate() == 13);
   auto e24 = make_unique<NumberExpression>(24);
   auto s13_24 = SumExpression(move(e13),move(e24));
   REQUIRE(s13_24.evaluate()==37);
   auto add1234 = make_unique<SumExpression>(
         make_unique<SumExpression>(make_unique<NumberExpression>(1),
                                    make_unique<NumberExpression>(2)),
         make_unique<SumExpression>(make_unique<NumberExpression>(3),
         make_unique<NumberExpression>(4))
         );
   std::cout << add1234->toString() << "\n";
   REQUIRE(add1234->evaluate()==10);
   auto mul34 = make_unique<MultiplyExpression>(makeNumber(3),makeNumber(4));
   REQUIRE(mul34->evaluate()==12);
}
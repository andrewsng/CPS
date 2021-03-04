//
// Created by Chris Hartman on 3/1/21.
//

#ifndef CS372SPRING2021EXAMPLECODE_EXPRESSION_HPP
#define CS372SPRING2021EXAMPLECODE_EXPRESSION_HPP
#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
   [[nodiscard]] virtual int evaluate() const = 0;
   [[nodiscard]] virtual std::string toString() const = 0;
   virtual ~Expression() = default;
};

class SumExpression : public Expression {// E -> E + E
public:
   [[nodiscard]] int evaluate() const override;
   [[nodiscard]] std::string toString() const override;
   SumExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};

class MultiplyExpression : public Expression {// E -> E * E
public:
   [[nodiscard]] int evaluate() const override;
   [[nodiscard]] std::string toString() const override;
   MultiplyExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};

class SubtractExpression : public Expression {// E -> E - E
public:
   [[nodiscard]] int evaluate() const override;
   [[nodiscard]] std::string toString() const override;
   SubtractExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};

class DivideExpression : public Expression {// E -> E / E
public:
   [[nodiscard]] int evaluate() const override;
   [[nodiscard]] std::string toString() const override;
   DivideExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
private:
   std::unique_ptr<Expression> _lhs;
   std::unique_ptr<Expression> _rhs;
};

class NumberExpression : public Expression { // E -> [number]
public:
   [[nodiscard]] int evaluate() const override;
   [[nodiscard]] std::string toString() const override;
   explicit NumberExpression(int);

private:
   int _number;
};
#endif//CS372SPRING2021EXAMPLECODE_EXPRESSION_HPP

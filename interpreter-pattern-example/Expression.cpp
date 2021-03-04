//
// Created by Chris Hartman on 3/1/21.
//

#include "Expression.hpp"
using std::move;
using std::string;

SumExpression::SumExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
   :_lhs(move(lhs)),_rhs(move(rhs))
{}

int SumExpression::evaluate() const {
   return _lhs->evaluate() + _rhs->evaluate();
}

string SumExpression::toString() const  {
   return "(" + _lhs->toString() + "+" + _rhs->toString() + ")";
}

MultiplyExpression::MultiplyExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
      :_lhs(move(lhs)),_rhs(move(rhs))
{}

int MultiplyExpression::evaluate() const {
   return _lhs->evaluate() * _rhs->evaluate();
}

string MultiplyExpression::toString() const  {
   return _lhs->toString() + "*" + _rhs->toString();
}

SubtractExpression::SubtractExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
      :_lhs(move(lhs)),_rhs(move(rhs))
{}

int SubtractExpression::evaluate() const {
   return _lhs->evaluate() - _rhs->evaluate();
}
string SubtractExpression::toString() const  {
   return _lhs->toString() + "-" + _rhs->toString();
}

DivideExpression::DivideExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
      :_lhs(move(lhs)),_rhs(move(rhs))
{}

int DivideExpression::evaluate() const {
   return _lhs->evaluate() / _rhs->evaluate();
}
string DivideExpression::toString() const  {
   return _lhs->toString() + "/" + _rhs->toString();
}

NumberExpression::NumberExpression(int num) : _number(num)
{}

int NumberExpression::evaluate() const {
   return _number;
}

string NumberExpression::toString() const  {
   return std::to_string(_number);
}

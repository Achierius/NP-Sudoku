#include "clause.hpp"

#include <assert.h>
#include <vector>
#include <iostream>

Clause::Operator o0 = Clause::Operator::kIdentity;
Clause::Operator o1 = Clause::Operator::kNegate;
Clause::Operator o2 = Clause::Operator::kAnd;
Clause::Operator o3 = Clause::Operator::kNand;
Clause::Operator o4 = Clause::Operator::kOr;
Clause::Operator o5 = Clause::Operator::kNor;
Clause::Operator o6 = Clause::Operator::kXor;
Clause::Operator o7 = Clause::Operator::kNxor;

void testInit() {
  Clause cl_a;
  Clause cl_b(o1);
  Clause cl_c(o2);
  Clause cl_d(o0);
  Clause cl_e(o7);
  assert(cl_a.getOperator() == o0);
  assert(cl_b.getOperator() == o1);
  assert(cl_c.getOperator() == o2);
  assert(cl_d.getOperator() == o0);
  assert(cl_e.getOperator() == o7);

  assert(!cl_a.evaluate().determined());
  assert(!cl_b.evaluate().determined());
  assert(!cl_c.evaluate().determined());

  Clause cl_f(cl_a, o1);
  assert(!cl_f.evaluate().determined());

  std::vector<Clause> cls;
  cls.push_back(cl_b);
  cls.push_back(cl_c);
  Clause cl_g(cls, o2);
  assert(!cl_g.evaluate().determined());
}

void testOperator() {
  Clause cl_a;
  assert(cl_a.getOperator() == o0);
  cl_a.negate();
  assert(cl_a.getOperator() == o1);
  cl_a.setOperator(o3);
  assert(cl_a.getOperator() == o3);
  cl_a.negate();
  assert(cl_a.getOperator() == o2);
  cl_a.setOperator(o7);
  assert(cl_a.getOperator() == o7);
}

void testEquals() {
  Clause cl_a;
  assert(!cl_a.evaluate().determined());
  assert(cl_a.getOperator() == o0);
  Clause cl_b(cl_a, o3);
  assert(cl_b.getOperator() == o3);
  assert(cl_b.evalNum() == 1);
  cl_a = cl_b;
  assert(cl_a.getOperator() == o3);
  assert(cl_a.evalNum() == 1);
}

int main() {
  testInit();
  testOperator();
  testEquals();
}
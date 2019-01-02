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

void testPrint() {
  Clause c_a;
  Clause c_b(c_a, o2);
  c_b.addClause(c_a);
  Clause c_d(c_a, o3);
  c_d.addClause(c_a);

  Clause c_e;
  c_e.setOperator(o4);
  c_e.addClause(c_a);
  c_e.addClause(c_d);
  c_e.addClause(c_d);
  c_e.addClause(c_a);

  Clause c_long;
  Clause c_longg(c_long, o1);
  Clause c_longgg(c_longg, o0);
  Clause c_longggg(c_longgg, o1);
  Clause c_longgggg(c_longggg, o0);
  Clause c_boi(c_longgggg, o2);
  c_boi.addClause(c_longgg);

  Clause c_q(o6);
  Clause c_qq(o5);
  c_qq.addClause(c_a);
  c_qq.addClause(c_a);
  c_q.addClause(c_qq);
  c_q.addClause(c_qq);
  c_q.addClause(c_qq);

  c_b.addClause(c_boi);
  c_b.addClause(c_d);
  c_b.addClause(c_e);
  c_b.addClause(c_a);
  c_b.addClause(c_q);

  //c_b.print_tree();
}

void testCNF() {
  Clause an_1;
  Clause an_2(an_1, o3);
  Clause an_3(o1);
  an_2.addClause(an_3);

  std::vector<Clause> init;
  init.push_back(an_1);
  init.push_back(an_1);
  init.push_back(an_2);
  Clause c_and(init, o2);
  Clause c_or(init, o4);

  Clause test_a;
  test_a.setOperator(o2);
  for(int i = 0; i < 9; i++) {
    if(i % 3) {
      test_a.addClause(c_or);
    } else {
      test_a.addClause(c_and);
    }
  }
  Clause c_andd(c_and, o2);
  c_andd.addClause(c_and);
  c_andd.addClause(c_andd);
  test_a.addClause(c_andd);

  test_a.cnf();

  Clause a(o2);
  Clause o(o4);
  Clause e;
  o.addClause(e);
  o.addClause(e);
  for(int i = 0; i < 40; i++) {
    a.addClause(o);
  }
  a.print_tree();
}

int main() {
  testInit();
  testOperator();
  testEquals();
  testNegate();
  testReduce();
  testDepth();
  testPrint();
  testCNF();
}

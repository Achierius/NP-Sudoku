#include <assert.h>
#include <vector>
#include <iostream>

#include "model_parser.hpp"
#include "model.hpp"
#include "cnf_equation.hpp"

void testSize() {
  Model model;
  CNFEquation eqn = parseModel(model);
  std::cout<<"Eqn 1: "<<eqn.numClauses()<<" clauses."<<std::endl;
  assert(eqn.numClauses() == 11988); //See paper for details on why there should be this many clauses

  model.set(1, 7);
  eqn = parseModel(model);
  std::cout<<"Eqn 2: "<<eqn.numClauses()<<" clauses.\n";
  assert(eqn.numClauses() == 11989); //Same # of clauses as eqn_1 but with one additional to set index 1 to 7
}

int main() {
  testSize();
}
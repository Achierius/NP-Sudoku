#ifndef __NP_SUDOKU_MODEL_PARSER
#define __NP_SUDOKU_MODEL_PARSER

#include "model.hpp"
#include "cnf_equation.hpp"

int variableID(int i, int j, int k);

Model& parseEqns(const CNFEquation& eqn);

CNFEquation& parseModel(const Model& model);

bool verifyEqn(const CNFEquation& eqn);

bool verifyModel(const Model& model);

#endif//__NP_SUDOKU_MODEL_PARSER

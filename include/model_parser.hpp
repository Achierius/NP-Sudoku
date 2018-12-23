#ifndef __NP_SUDOKU_MODEL_PARSER
#define __NP_SUDOKU_MODEL_PARSER

#include "model.hpp"
#include "clause.hpp"

Model parseEqns(const Clause& eqns);

Clause& parseModel(const Model& model);

bool verifyEqns(const Clause& eqns);

bool verifyModel(const Model& model);

#endif//__NP_SUDOKU_MODEL_PARSER

#ifndef __NP_SUDOKU_MODEL_PARSER
#define __NP_SUDOKU_MODEL_PARSER

#include "model.hpp"

Model parseEqns(const std::vector<LinearEquation>& eqns);

std::vector<LinearEquation> parseModel(const Model& model);

bool verifyEqns(const std::vector<LinearEquation>& eqns);

bool verifyModel(const Model& model);

#endif//__NP_SUDOKU_MODEL_PARSER

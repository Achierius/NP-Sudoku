#ifndef __NP_SUDOKU_SAT_SOLVER
#define __NP_SUDOKU_SAT_SOLVER

#include <vector>

#include "clause.hpp"

class SatSolver {
public:
  SatSolver();

  ~SatSolver();
  SatSolver(const SatSolver& to_copy);
  SatSolver& operator=(const SatSolver& to_copy);

  virtual bool satisfiable() = 0;
  virtual std::vector<bool> solve() = 0;

private:
};

#endif//__NP_SUDOKU_SAT_SOLVER
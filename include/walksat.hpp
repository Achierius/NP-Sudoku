#ifndef __NP_SUDOKU_WALKSAT
#define __NP_SUDOKU_WALKSAT

#include "sat_solver.hpp"

class WalkSAT : public SatSolver {
public:
  WalkSAT();

  ~WalkSAT();

  bool satisfiable();
  std::vector<CNFVariable> solve();
private:
};

#endif//__NP_SUDOKU_WALKSAT
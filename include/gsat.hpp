#ifndef __NP_SUDOKU_GSAT
#define __NP_SUDOKU_GSAT

#include "sat_solver.hpp"

class GSAT : public SatSolver {
public:
  GSAT();

  ~GSAT();

  bool satisfiable();
  std::vector<CNFVariable> solve();
private:
};

#endif//__NP_SUDOKU_GSAT
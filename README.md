# NP-Sudoku
Building a SAT Solver to solve standard 9x9 Sudoku problems.

The core of this project is the effective and efficient implementation of the WalkSAT boolean satisfiability solver.
A standard sudoku board can be represented as a series of 11000+ boolean equations; once so represented,
finding a solution to the given sudoku problem is simple.

This project includes a representation of a standard sudoku board, multiple representations of the relevant boolean
equations, an input/output manager, and implementations of the GSAT and WalkSAT solver algorithms.

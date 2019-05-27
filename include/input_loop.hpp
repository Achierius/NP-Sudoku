#ifndef __NP_SUDOKU_INPUT_LOOP
#define __NP_SUDOKU_INPUT_LOOP

#include <vector>
#include <tuple>
#include <string>
#include "model.hpp"

/* Also holds commands exit, quit, q, auto-show, timeout, try, clear */
void inputLoop();

/* Command: load random
 *          load example <name>
 *          load new <path>
 * Loads new Sudoku board model.
 */
Model commandLoad(int option, std::string dest);

/* Command: display instance
 *          display solution
 *          display pretty-solution
 * Print board or solution to board.
 * Return 1 if display target DNE, else 0.
 */
int commandDisplay(int option);

/* Command: Show
 * Attempts the following commands in order until one returns 0:
 * display pretty-solution
 * display solution
 * display instance
 * Return 1 if {display instance} returns 0, else 0.
 */
int commandShow();

/* Command: solve <solver>
 * Attempts to solve current Instance with target solver.
 * Return values:
 *  0: Success
 *  1: Solver not found
 *  2: No board loaded
 *  3: Solver could not solve board / timed out
 */
int commandSolve(std::string solver);

/* Command: solve <i> <j> <val>
 * Sets the ith row, jth column entry of the Instance -- (i, j) -- to val.
 * If val = 0, empties (i, j).
 * Return 0 if success, 1 if val > 9 || val < 0, 2 if Instance DNE.
 */
int commandEdit(int i, int j, int val);

/* Command: edit<i> <j> <val>
 * Sets the ith row, jth column entry of the Solution -- (i, j) -- to val.
 * If val = 0, empties (i, j).
 * Return 0 if success, 1 if val > 9 || val < 0, 2 if Instance DNE.
 */
int commandSolve(int i, int j, int val);

#endif//__NP_SUDOKU_INPUT_LOOP

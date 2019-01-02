#ifndef __NP_SUDOKU_CNF_EQUATION
#define __NP_SUDOKU_CNF_EQUATION

#include "cnf_variable.hpp"
#include "cnf_handler.hpp"

#include <array>
#include <vector>
#include <memory>
#include <tuple>
#include <list>

class CNFEquation {
public:
  using CNFClause = std::vector<CNFVariable::VarSize>;

  friend CNFHandler;

  CNFEquation();
  CNFEquation(std::vector<CNFClause> clauses);

  CNFEquation(const CNFEquation& to_copy);
  CNFEquation& operator=(const CNFEquation& to_copy);
  ~CNFEquation() = default;

  /** Returns the number of clauses in _equation.
   */
  int numClauses();
  /** Returns the number of variables in _variables
   *  that are active in _equation.
   */
  int numVariables();
  /** Returns a list of variables currently in use. */
  std::vector<CNFVariable::VarSize> getVariables();

  /** Returns true if a variable is in use and is determined. */
  bool hasValue(CNFVariable::VarSize varName);
  /** Returns the value of a variable if hasValue, otherwise false. */
  bool getVariableValue(CNFVariable::VarSize varName);
  /** Returns true if the variable is in use. */
  bool isVariable(CNFVariable::VarSize varName);

  /** Adds a clause to the end of _equation. */
  void addClause(CNFClause new_clause);
  /** Returns the clause at the given index, or an emmpty clause if
   *  the index is more than numClauses();
   */
  CNFClause getClause(int index);
  /** Removes a clause at the given index, or noops if index>numClauses(). */
  void removeClause(int index);

  /** Returns true if:
   *  All variables referenced by the CNFClause have values
   *  and exist within variables_,
   *  or if at least one variable referenced by the CNFClause
   *  has a value of false.
   *  Otherwise returns false.
   */
  bool canEvalClause(CNFClause to_eval);
  /** Evaluates the value of the given CNFClause by performing
   *  lookups on the CNFVariables within variables_ and
   *  logical or'ing them by eachother. If any has a value of false,
   *  evalClause will return false. If canEvalClause is false,
   *  evalClause will return false.
   */
  bool evalClause(CNFClause to_eval);

private:

  /** This is a list because we want pointers to members
   *  of this container to remain valid after a resize.
   *  Access should not actually be done through the list's
   *  access operators, but through the handlers --
   *  our SAT solver implementation will be making decisions
   *  based off of individual variables and the number of clauses
   *  they affect, so we can simply use the stored pointers
   *  each handler will contain to modify or look at the relevant
   *  clauses.
   */
  std::list<CNFClause> equation_;

  /** Stores reference data for every possible CNFVariable for
   *  this equation. If std::get<1> of an entry is false, that
   *  variable is not present in this equation and the data inside
   *  the CNFHandler is just a placeholder. All CNFHandlers and
   *  contained CNFVariables should be initialized at the construction
   *  of the CNFEquation. Each CNFHandler contains pointers to every
   *  CNFClause that contains their handled variable; it is the
   *  responsibility of the CNFEquation to keep the CNFHandler's back-
   *  reference list updated as the CNFEquation updates with new clauses.
   *  The index of a given CNFVariable in the array is equal to their
   *  identifier_ value minus 1.
   */
  std::array<std::tuple<CNFHandler, bool>, CNFVariable::NUM_IDENTIFIERS> variables_;

  /** Calculates the number of unique-identifier variables present
   *  in equation_ and assigns that value to numVariables_.
   *  Assumes variables_ is correctly updated to match the current
   *  state of equation_.
   */
  void recalcNumVariables();

  /** Number of unique-identifier variables present in equation_.
   *  Updated periodically by recalcNumVariables().
  */
  int numVariables_;
};

#endif//__NP_SUDOKU_CNF_EQUATION
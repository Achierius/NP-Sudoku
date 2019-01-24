#ifndef __NP_SUDOKU_CNF_HANDLER
#define __NP_SUDOKU_CNF_HANDLER

#include <vector>
#include <memory>

#include "cnf_variable.hpp"

template <class T>
class CNFHandler : public CNFVariable {
public:
  using CNFClause = std::vector<T>;

  /** Creates a handler with a default-constructed
   *  CNFVariable.
   */
  CNFHandler() { }
  CNFHandler(const CNFVariable& to_init) : CNFVariable(to_init) {}
  CNFHandler(const CNFVariable& to_init, const std::vector<std::shared_ptr<CNFClause> >& to_ref) : CNFVariable(to_init) {
    clauses_ = std::vector<std::shared_ptr<CNFClause> >(to_ref);
  }
  CNFHandler(const CNFHandler& to_copy) : CNFVariable(to_copy) {
    clauses_ = std::vector<std::shared_ptr<CNFClause> >(to_init.clauses_);
  }
  CNFVariable& operator=(const CNFHandler& to_copy) : CNFVariable(to_copy) {
    clauses_ = std::vector<std::shared_ptr<CNFClause> >(to_init.clauses_);
  }
  ~CNFHandler() = default;

  /** Each handler is supposed to keep a list of clauses
   *  pointing at this specific CNFVariable, and there's
   *  only supposed to be one CNFHandler per CNFEquation --
   *  copying them makes no sense!
   */
  CNFHandler(const CNFHandler<T>& to_copy) = delete;
  CNFHandler& operator=(const CNFHandler<T> & to_copy) = delete;
  ~CNFHandler() = default;

  //TODO: Move semantics

  /** Adds clause to clauses_ by creating a
   *  shared_ptr to point to it. Returns false
   *  if clause is already in clauses_, otherwise
   *  returns true. Does not add duplicate clauses.
   */
  bool addClause(CNFClause& new_clause) {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      if((**itr) == (*new_clause)) {
        return false;
      }
    }
    clauses_.push_back(std::make_shared<CNFClause>(new_clause));
    return true;
  }
  /** Removes given clause by checking equality
   *  with every clause in the list and removing the first
   *  clause to match.
   */
  bool removeClause(CNFClause& old_clause) {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      if((**itr) == (*old_clause)) {
        clauses_.erase(itr);
        return true;
      }
    }
    return false;
  }

private:
  /** A (not necessarily complete) list of CNFClauses
   *  containing a pointer to this variable. CNFHandler
   *  is responsible for all clauses in this object.
   *  Should contain a complete list of CNFClauses
   *  containing a pointer to this variable belonging to
   *  a specific CNFEquation for at least one CNFEquation.
   *  The pointer-references will remain valid during the
   *  lifespan of the given CNFEquation. */
  std::vector<std::shared_ptr<CNFClause> > clauses_;
};

#endif//__NP_SUDOKU_CNF_HANDLER
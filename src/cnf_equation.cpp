#include "cnf_equation.hpp"
#include <algorithm>

CNFEquation::CNFEquation() {

}

CNFEquation::CNFEquation(const CNFEquation& to_copy) {

}
CNFEquation& CNFEquation::operator=(const CNFEquation& to_copy) {

}
CNFEquation::~CNFEquation() = default;

CNFEquation::CNFEquation(const std::initializer_list<clause_t>& clauses) {

}

CNFEquation::CNFEquation(const std::initializer_list<clause_t>& clauses,
            std::initializer_list<value_t>) {

}

void CNFEquation::setVariable(variable_t variable, value_t new_val) {
  variables_[variable] = new_val;
}
void CNFEquation::setRange(variable_t min, variable_t max, value_t new_val) {
  for(variable_t i : {min, max}) {
    setVariable(i, new_val);
  }
}
void CNFEquation::setAll(value_t new_val) {
  setRange(CNF_MIN, CNF_MAX, new_val);
}

CNFEquation::value_t CNFEquation::getVariable(variable_t variable) const {
  return variables_[variable];
}

void CNFEquation::addClause(const clause_t& new_clause) {
  clauses_.push_back(std::make_shared<clause_t>(new_clause));
  for(auto i : new_clause) {
    references_[i.first].push_back(std::make_shared<clause_t>(new_clause));
  }
}
void CNFEquation::removeClause(const clause_t& clause_to_delete) {
  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    if((**itr) == clause_to_delete) {
      clauses_.erase(itr);
      break;
    }
  }
  for(auto i : clause_to_delete) {
    references_[i.first].erase(std::remove_if(references_.begin(), references_.end(),
                   [=](std::shared_ptr<clause_t> arg){return *arg == clause_to_delete;}));
    if(i.first == maxVariable() && references_[i.first].size() == 0) {
      reparseMaxVariable();
    }
  }
}

std::vector<std::shared_ptr<const CNFEquation::clause_t> > CNFEquation::varClauses(variable_t variable) {

}
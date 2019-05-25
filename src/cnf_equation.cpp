#include "cnf_equation.hpp"
#include <algorithm>

CNFEquation::CNFEquation() {
  max_variable_ = -1;
  for(auto i : variables_) {
    i.reset();
  }
}

CNFEquation::CNFEquation(const CNFEquation& to_copy){
  for(auto i : {CNF_MIN, CNF_MAX}) {
    variables_[i] = to_copy.variables_[i];
  }
  for(auto i : to_copy.clauses_) {
    clauses_.push_back(i);
  }
  reparseCReferences();
  reparseMaxVariable();
}

CNFEquation& CNFEquation::operator=(const CNFEquation& to_copy) {
  for(auto i : {CNF_MIN, CNF_MAX}) {
    variables_[i] = to_copy.variables_[i];
  }
  for(auto i : to_copy.clauses_) {
    clauses_.push_back(i);
  }
  reparseCReferences();
  reparseMaxVariable();
  return *this;
}

CNFEquation::~CNFEquation() = default;

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

std::pair<CNFEquation::variable_t, bool> CNFEquation::makePair(variable_t variable, bool negated) {
  return std::pair<variable_t, bool>(variable, negated);
}

void CNFEquation::addVariable(variable_t variable, bool negated) {
  //clause_t a;
  //a.push_back(makePair(variable, negated));
  //addClause(a);
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
    (references_[i.first]).erase(std::remove_if(references_[i.first].begin(), references_[i.first].end(),
                                 [=](std::shared_ptr<clause_t> arg){return *arg == clause_to_delete;}),
                                 references_[i.first].end());
    if(i.first == maxVariable() && references_[i.first].size() == 0) {
      reparseMaxVariable();
    }
  }
}

CNFEquation::variable_t CNFEquation::maxVariable() const {
  return max_variable_;
}

const std::vector<std::shared_ptr<CNFEquation::clause_t> > CNFEquation::varClauses(variable_t variable) {
  return references_[variable];
}

const std::list<std::shared_ptr<CNFEquation::clause_t> > CNFEquation::allClauses() {
  return clauses_;
}

int CNFEquation::numClauses() {
  return clauses_.size();
}

void CNFEquation::reparseMaxVariable() {
  max_variable_ = -1;
  for(variable_t i = CNF_MAX; i >= CNF_MIN; i--) {
    if(references_[i].size() > 0) {
      max_variable_ = i;
      return;
    }
  }
}

void CNFEquation::reparseCReferences() {
  for(std::shared_ptr<clause_t> itr : clauses_) {
    for(auto num : *itr) {
      references_[num.first].push_back(itr);
    }
  }
}
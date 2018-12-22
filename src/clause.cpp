#include "clause.hpp"

Clause::Clause() {
  operator_ = Operator::kIdentity;
}

Clause::Clause(std::vector<Clause> init, Operator opr) {
  clauses_ = std::vector<Clause>(init);
  operator_ = opr;
}

Clause::Clause(Clause& init, Operator opr) {
  clauses_ = std::vector<Clause>();
  clauses_.push_back(init);
  operator_ = opr;
}

Clause::~Clause() { }

Clause& Clause::operator=(const Clause& to_copy) {
  clauses_ = std::vector<Clause>(to_copy.clauses_);
  operator_ = to_copy.operator_;
}

Clause::Clause(const Clause& to_copy) {
  clauses_ = std::vector<Clause>(to_copy.clauses_);
  operator_ = to_copy.operator_;
}

void Clause::negate() {
  operator_ = (Clause::Operator)(1 - (operator_ % 2));
}

void Clause::setOperator(Clause::Operator new_opr) {
  operator_ = (Clause::Operator)__max(0, (int)new_opr % 8);
}

Clause::Operator Clause::getOperator() {
  return operator_;
}

int Clause::numClauses() {

}

void Clause::addClause(Clause& clause) {

}

void Clause::insertClause(Clause& clause, int index) {

}

Clause& Clause::getClause(int index) {

}

Clause& Clause::removeClause(int index) {

}

int Clause::evalNum() {

}

Bit Clause::evaluate() {

}
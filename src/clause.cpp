#include "clause.hpp"

Clause::Clause() {
  operator_ = Operator::kIdentity;
}

Clause::Clause(Operator opr) {
  operator_ = opr;
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
  return clauses_.size();
}

void Clause::addClause(Clause& clause) {
  clauses_.push_back(clause);
}

void Clause::insertClause(Clause& clause, int index) {
  auto itr = clauses_.begin();
  for(int i = 0; itr != clauses_.end() && i < index; i++) {
    itr++;
  }
  clauses_.insert(itr, clause);
}

Clause& Clause::getClause(int index) {
  return clauses_[index];
}

Clause& Clause::removeClause(int index) {
  auto itr = clauses_.begin();
  for(int i = 0; itr != clauses_.end() && i < index; i++) {
    itr++;
  }
  clauses_.erase(itr);
}

int Clause::evalNum() {
  if(numClauses() == 0) {
    return 1;
  }

  int sum = 0;
  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    sum += itr->evalNum();
  }
  return sum;
}

Bit Clause::evaluate() {
  Bit bit;
  if(numClauses() == 0) {
    return bit;
  }

  if(operator_ == Operator::kIdentity) {
    return clauses_[0].evaluate();
  }
  else if(operator_ == Operator::kNegate) {
    bit = clauses_[0].evaluate();
    bit.flip();
    return bit;
  }

  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    Bit eval = itr->evaluate();
    if(!eval.determined()) {
      return bit;
    }
    bool fail = false;
    switch(operator_) {
      case Operator::kAnd:
        fail = !eval.state();
        break;
      case Operator::kNand:
        fail = eval.state();
        break;
      case Operator::kOr:
        fail = !eval.state() || !bit.state();
        break;
      case Operator::kNor:
        fail = eval.state() || bit.state();
        break;
      case Operator::kXor:
        fail = eval.state() == bit.state();
        break;
      case Operator::kNxor:
        fail = eval.state() != bit.state();
        break;
    }
    if(fail) {
      bit.setOff();
      return bit;
    }
  }
  bit.setOn();
  return bit;
}
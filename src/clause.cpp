#include "clause.hpp"

#include <algorithm>
#include <iostream>
#include <tuple>
#include <string>
#include <stack>

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
  operator_ = (Clause::Operator)(operator_ + (1 - 2 * (operator_ % 2)));
}

void Clause::setOperator(Clause::Operator new_opr) {
  operator_ = (Clause::Operator)std::max(0, (int)new_opr % 8);
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

Clause* Clause::getClause(int index) {
  return &clauses_[index];
}

void Clause::removeClause(int index) {
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

bool Clause::reduce() {
  bool ret = false;

  if(this->numClauses() == 0) {
    return ret;
  }

  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    ret = ret || itr->reduce();
  }

  //Rule 1: Identity reduction
  if(operator_ == Operator::kIdentity) {
    this->operator_ = clauses_[0].operator_;
    this->clauses_ = std::vector<Clause>(clauses_[0].clauses_);
    ret = true;
  }

  //Rule 2: Negation reduction
  if(operator_ == Operator::kNegate) {
    this->operator_ = clauses_[0].operator_;
    this->clauses_ = std::vector<Clause>(clauses_[0].clauses_);
    negate();
    ret = true;
  }

  //Rule 3: Same operator collapse
  std::vector<Clause> to_extend;
  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    if(itr->getOperator() == getOperator()) {
      to_extend.reserve(to_extend.size() + itr->clauses_.size());
      to_extend.insert(to_extend.end(), itr->clauses_.begin(), itr->clauses_.end());
      ret = true;
    }
  }
  clauses_.erase(
    std::remove_if(clauses_.begin(), clauses_.end(), [this](Clause c){return c.getOperator() == getOperator();}),
    clauses_.end());
  clauses_.reserve(clauses_.size() + to_extend.size());
  clauses_.insert(clauses_.end(), to_extend.begin(), to_extend.end());
  return ret;
}

bool Clause::identityCompress() {
  bool ret = false;
  if(numClauses() == 0) {
    return ret;
  }

  if(operator_ == kIdentity) {
    clauses_.erase(clauses_.begin() + 1, clauses_.end());
    operator_ = clauses_[0].operator_;
    clauses_ = std::vector<Clause>(clauses_[0].clauses_);
    ret = true;
    identityCompress();
  } else {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      ret = ret || itr->identityCompress();
    }
  }

  return ret;
}

bool Clause::negationDecompress() {
  bool ret = false;
  if(numClauses() == 0) {
    return ret;
  }

  if(operator_ % 2 == 1) {
    std::vector<Clause> old_clauses(clauses_);
    Operator new_operator = (Operator)(operator_ - 1);
    Clause new_child(old_clauses, new_operator);

    operator_ = kNegate;
    clauses_.clear();
    clauses_.push_back(new_child);

    clauses_[0].negationDecompress();

    ret = true;
  } else {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      ret = ret || itr->negationDecompress();
    }
  }
}

bool Clause::operatorCompress() {
  bool ret = false;
  if(numClauses() == 0) {
    return ret;
  }

  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    ret = ret || itr->operatorCompress();
  }

  std::vector<Clause> to_extend;
  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    if(itr->getOperator() == getOperator()) {
      to_extend.reserve(to_extend.size() + itr->clauses_.size());
      to_extend.insert(to_extend.end(), itr->clauses_.begin(), itr->clauses_.end());
      ret = true;
    }
  }
  clauses_.erase(
    std::remove_if(clauses_.begin(), clauses_.end(), [this](Clause c){return c.getOperator() == getOperator();}),
    clauses_.end());
  clauses_.reserve(clauses_.size() + to_extend.size());
  clauses_.insert(clauses_.end(), to_extend.begin(), to_extend.end());

  return ret;
}

void Clause::negationSink() {
  if(numClauses() == 0) {
    negate();
  } else {
    if(operator_ == kAnd) {
      operator_ == kOr;
    } else if (operator_ == kOr) {
      operator_ == kAnd;
    }
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      itr->negationSink();
    }
  }
}
bool Clause::negationDescend() {
  bool ret = false;
  if(numClauses() == 0) {
    return ret;
  }

  if(operator_ == kNegate) {
    clauses_.erase(clauses_.begin() + 1, clauses_.end());
    clauses_[0].negationSink();
    operator_ = clauses_[0].getOperator();
    clauses_ = std::vector<Clause>(clauses_[0].clauses_);

    ret = true;
  } else {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      itr->negationDescend();
    }
  }

  return ret;
}

bool Clause::cnf() {
  bool ret = false;
  //Step 1: Remove all Xor/Nxor operators
  //Step 2: Compress all identity operators
  ret = ret || identityCompress();
  //Step 3: Decompress all negation operators
  ret = ret || negationDecompress();
  //Step 4: Descend negation operators downwards
  ret = ret || negationDescend();
  //Step 5: Compact repeated operators
  ret = ret || operatorCompress();
  //Step 6: Distribute And operators
  //Step 7: Distribute Or operators
}

int Clause::depth() {
  int ret = 0;
  for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
    ret = std::max(ret, itr->depth());
  }
  return ret + 1;
}

void Clause::print_tree() {
  int offset = 0;
  std::string* lines = new std::string[depth()];
  std::string* inter = new std::string[depth() - 1];
  int* displacement = new int[depth()];
  for(int i = 0; i < depth(); i++) {
    displacement[i] = 0;
    lines[i] = "";
    if(i < depth() - 1){
      inter[i] = "";
    }
  }

  {
    std::stack<std::tuple<Clause*, int, int> > fringe;
    fringe.push(std::make_tuple(this, 0, 0));
    Clause* current;
    int depth;
    int deepiness;

    while(!fringe.empty()) {
      current = std::get<0>(fringe.top());
      depth = std::get<1>(fringe.top());
      deepiness = std::get<2>(fringe.top());
      fringe.pop();

      int offset = std::max(displacement[depth], deepiness) - lines[depth].length();

      if(offset > 0) {
        lines[depth] += std::string(offset, ' ') + current->displayFancy() + " ";
      } else {
        lines[depth] += current->displayFancy() + " ";
      }
      for(int i = 0; i < depth; i++) {
        displacement[i] = lines[depth].length();
      }
      for(auto itr = current->clauses_.rbegin(); itr != current->clauses_.rend(); itr++) {
        fringe.push(std::make_tuple(&(*itr), depth + 1, lines[depth].length() - 3));
      }
    }

    int maxLength = 0;
    for(int i = 0; i < this->depth(); i++) {
      maxLength = std::max((size_t)maxLength, lines[i].length());
    }
    for(int i = 0; i < this->depth(); i++) {
      while(lines[i].length() < maxLength) {
        lines[i] += ' ';
      }
    }
    for(int i = 0; i < this->depth() - 1; i++) {
      bool inToken = false;
      bool cont = false;
      for(int j = 0; j < lines[i].length() && j < lines[i + 1].length(); j++) {
        if(lines[i][j] == ' ' && lines[i + 1][j] == ' ') {
          if(cont) {
            inter[i] += '-';
          } else {
            inter[i] += ' ';
          }
        } else if(lines[i][j] == ' ' && lines[i + 1][j] != ' ') {
          if(inToken) {
            inToken = false;
            bool needChar = true;
            for(int k = j + 1; k < lines[i].length(); k++) {
              if(lines[i][k] != ' ') {
                cont = false;
                needChar = false;
                inter[i] += ' ';
                break;
              } else if (lines[i + 1][k] != ' ') {
                cont = true;
                needChar = false;
                inter[i] += '-';
                break;
              }
            }
            if(needChar) {
              cont = false;
              //inter[i] += ' ';
            }
          } else {
            inToken = true;
            inter[i] += '\\';
          }
        } else if(lines[i][j] != ' ' && lines[i + 1][j] == ' ') {
          if(cont) {
            inter[i] += '-';
          } else {
            inter[i] += ' ';
          }
        } else if(lines[i][j] != ' ' && lines[i + 1][j] != ' ') {
          if(inToken) {
            inToken = false;
            for(int k = j + 1; k < lines[i].length(); k++) {
              if(lines[i][k] != ' ') {
                cont = false;
                inter[i] += ' ';
                break;
              } else if (lines[i + 1][k] != ' ') {
                cont = true;
                inter[i] += '-';
                break;
              }
            }
          } else {
            inToken = true;
            inter[i] += '|';
          }
        }
      }
    }
  }

  std::cout<<lines[0]<<"\n";
  for(int i = 1; i < this->depth(); i++) {
    std::cout<<inter[i - 1]<<"\n";
    std::cout<<lines[i]<<"\n";
  }
  std::cout<<std::endl;

  delete[] lines;
  delete[] inter;
  delete[] displacement;
}

char Clause::display() {
  switch(operator_) {
    case kIdentity:
      return '=';
    case kNegate:
      return '!';
    case kAnd:
      return '&';
    case kNand:
      return '$';
    case kOr:
      return '|';
    case kNor:
      return '(';
    case kXor:
      return '^';
    case kNxor:
      return '_';
    default:
      return '?';
  }
}

std::string Clause::displayFancy() {
  switch(operator_) {
    case kIdentity:
      return "==";
    case kNegate:
      return "!!";
    case kAnd:
      return "&&";
    case kNand:
      return "!&";
    case kOr:
      return "||";
    case kNor:
      return "!|";
    case kXor:
      return "^^";
    case kNxor:
      return "!^";
    default:
      return "??";
  }
}

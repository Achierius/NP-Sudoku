#ifndef __NP_SUDOKU_CNF_VARIABLE
#define __NP_SUDOKU_CNF_VARIABLE

#include <assert.h>
#include <iostream>

template <class T>
class CNFVariable {
public:
  /** Total number of possible identifiers, given a numerical type T. */
  const static unsigned long long NUM_IDENTIFIERS = 1ull << (8*sizeof(T) - 1);

  /** Object will have identifier_ == 1. */
  CNFVariable() {
    setValue(false);
    unset();
    setIdentifier(static_cast<T>(1));
  }
  CNFVariable(T identifier) {
    setValue(false);
    unset();
    setIdentifier(identifier);
  }
  CNFVariable(T identifier, bool initValue) {
    setValue(initValue);
    setIdentifier(identifier);
  }

  ~CNFVariable() = default;
  CNFVariable(const CNFVariable& to_copy) {
    setValue(to_copy.value_);
    if(!to_copy.determined_) {
      unset();
    }
    setIdentifier(to_copy.identifier_);
    setNegate(to_copy.negated());
  }
  CNFVariable& operator=(const CNFVariable& to_copy) {
    setValue(to_copy.value_);
    if(!to_copy.determined_) {
      unset();
    }
    setIdentifier(to_copy.identifier_);
    setNegate(to_copy.negated());
  }

  /** Returns value of the object if it contains a valid boolean
   *  value; if !determined(), assertion will fail. If negated(),
   *  returns !value.
   */
  bool value() const {
    assert(determined());
    if(!determined()) {
      return false;
    }
    if(negated()) {
      return !value_;
    }
    return value_;
  }
  /** Sets value of the object and marks the object as containing
   *  a valid boolean value. */
  void setValue(bool newValue) {
    determined_ = true;
    value_ = newValue;
  }

  /** Returns true if this object contains a valid boolean value. */
  bool determined() const {
    return determined_;
  }
  /** Invalidate the value held by this object and set determined_
   *  to false. No affect if determined_ == false. */
  void unset() {
    determined_ = false;
  }

  /** Returns the value of negated_. */
  bool negated() const {
    return negated_;
  }
  /** Set negated_ to equal !negated_. */
  void negate() {
    negated_ = !negated_;
  }
  /** A negate value of true will cause value() to return !value_. */
  void setNegate(bool new_state) {
    negated_ = new_state;
  }

  /** Identifiers must be within the range defined by the type of T.
   *  Setting the identifier to equal -VAL is equivalent to
   *  setting the identifier to equal  VAL and calling setNegate(1). */
  void setIdentifier(T identifier) {
    if(identifier < static_cast<T>(0)) {
      identifier_ = -identifier;
      setNegate(true);
    } else {
      identifier_ = identifier;
      setNegate(false);
    }
  }
  /** Returns identifier. As identifier_ is always stored as a
   *  positive value, a negative value is returned if negated_ is true.
  */
  T getIdentifier() const {
    if(negated()) {
      return -identifier_;
    } else {
      return identifier_;
    }
  }
  /** Returns true if the identifier casts to a char between 33 and 126 inclusive,
   *  or the corresponding negative values. Excludes all non-printable
   *  chars, as well as +-32 (Space) and +-127 (Delete). */
  bool printable() const {
    char val = static_cast<T>(identifier_);
    if(val > 32 && val < 127) {
      return true;
    }
    return false;
  }

private:
  /** Numerical representation of this object. */
  T identifier_;

  /** Causes value() to return !value_ if true. */
  bool negated_;
  /** If true, value_ is guaranteed to have a valid
   *  boolean value. If false, this object is considered
   *  to be undetermined and value() should not be called. */
  bool determined_;
  /** Boolean value of the object if determined_ is true,
   *  otherwise has no meaning. */
  bool value_;
};

#endif//__NP_SUDOKU_CNF_VARIABLE
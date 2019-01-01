#ifndef __NP_SUDOKU_CNF_VARIABLE
#define __NP_SUDOKU_CNF_VARIABLE

class CNFVariable {
public:
  using VarSize = char;
  /** Total number of possible identifiers, given a 1 byte char. */
  const static int NUM_IDENTIFIERS = 2 << (8*sizeof(VarSize) - 1);

  /** Object will have identifier_ == 1. */
  CNFVariable();
  CNFVariable(signed char identifier_);
  CNFVariable(signed char identifier_, bool initValue);

  ~CNFVariable();
  CNFVariable(const CNFVariable& to_copy);
  CNFVariable& operator=(const CNFVariable& to_copy);

  /** Returns value of the object if it contains a valid boolean
   *  value; if !determined(), value() will always return false. */
  bool value();
  /** Sets value of the object and marks the object as containing
   *  a valid boolean value. */
  void setValue();

  /** Returns true if this object contains a valid boolean value. */
  bool determined();
  /** Invalidate the value held by this object and set determined_
   *  to false. No affect if determined_ == false. */
  void unset();

  /** Returns the value of negated_. */
  bool negated();
  /** Set negated_ to equal !negated_. */
  void negate();
  /** A negate value of true will cause value() to return !value_. */
  void setNegate(bool new_state);

  /** Returns true if the identifier was successfully set.
   *  Identifiers must be signed char values not equal to 0 or -128.
   *  Setting the identifier to equal -VAL is equivalent to
   *  setting the identifier to equal  VAL and calling setNegate(1). */
  bool setIdentifier(signed char identifier);
  /** Returns identifier. As identifier_ is always stored as a
   *  positive value, a negative value is returned if negated_ is true.
  */
  signed char getIdentifier();
  /** Returns true if the identifier is between 33 and 126 inclusive,
   *  or the corresponding negative values. Excludes all non-printable
   *  chars, as well as +-32 (Space) and +-127 (Delete). */
  bool printable();

private:
  /** Character representation of this object. */
  signed char identifier_;

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
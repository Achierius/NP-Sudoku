#ifndef __NP_SUDOKU_LINEAR_EQUATION
#define __NP_SUDOKU_LINEAR_EQUATION

#include <vector>

/** Represent a linear equation in n variables of the form
  * a0*x0 + a1*x1 + ... + an*xn = c .
  */

class LinearEquation {
public:
    LinearEquation(); //0 = 0
    LinearEquation(std::vector<double> coefficients); //coeffs = 0
    LinearEquation(std::vector<double> coefficients, double constant);

    ~LinearEquation();
    LinearEquation(const LinearEquation toCopy);
    LinearEquation& operator=(const LinearEquation toCopy);
    
    bool validate(std::vector<double> values);
    double test(std::vector<double> values);
    LinearEquation substitute(int variable, double value);
    LinearEquation substitute(std::vector<int> variables, std::vector<double> values);

private:
    double _constant;
    std::vector<double> _coefficients;

};

#endif//__NP_SUDOKU_LINEAR_EQUATION

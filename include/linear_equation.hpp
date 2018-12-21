#ifndef __NP_SUDOKU_LINEAR_EQUATION
#define __NP_SUDOKU_LINEAR_EQUATION

#include <vector>
#include <string>

/** Represent a linear equation in n variables of the form
  * a0*x0 + a1*x1 + ... + an*xn = c .
  */

class LinearEquation {
public:
    LinearEquation(); //0 = 0
    LinearEquation(std::vector<double> coefficients); //coeffs = 0
    LinearEquation(std::vector<double> coefficients, double constant);

    ~LinearEquation();
    LinearEquation(const LinearEquation to_copy);
    LinearEquation& operator=(const LinearEquation to_copy);

    double constant() const;
    double coefficient(int variable) const;
    std::vector<double> coefficients() const;

    void setConstant(double new_constant);
    void setCoefficient(int variable, double new_coefficient);
    void setCoefficients(const std::vector<double>& new_coefficients);
    
    bool validate(const std::vector<double>& values) const;
    double test(const std::vector<double>& values) const;
    LinearEquation substitute(int variable, double value) const;
    LinearEquation substitute(const std::vector<int>& variables,
                              const std::vector<double>& values) const;

private:
    void testCoefficients(const std::vector<double>& coefficients, std::string tag) const;
    void testIndex(const int& index, std::string tag) const;

    double _constant;
    std::vector<double> _coefficients;

};

#endif//__NP_SUDOKU_LINEAR_EQUATION

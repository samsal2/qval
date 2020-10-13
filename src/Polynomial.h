//
//  Polynomial.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef Polynomial_h
#define Polynomial_h

#include <vector>

#include "MemDFac.h"
#include "MemDPow.h"

// the polynomial represents a (a + bx)^n expansion
class Polynomial {
 public:
  Polynomial(const double a, const double b, const std::size_t n);
  Polynomial(const std::vector<double>& coefficients);

  Polynomial& operator+=(const Polynomial& rhs);
  Polynomial& operator-=(const Polynomial& rhs);
  // can't pass by reference because of a *= a
  Polynomial& operator*=(const Polynomial rhs);
  Polynomial& operator*=(const double rhs);

  friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
  friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
  friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs);
  friend Polynomial operator*(Polynomial lhs, const double rhs);

  Polynomial getDerivative() const;
  Polynomial getIntegral() const;

  double eval(const double x) const;
  void printCoeff();

 private:
  std::vector<double> coeff;
};

Polynomial::Polynomial(const double a, const double b, const std::size_t n) {
  const MemDFac fac(n);
  const MemDPow aPow(a, n);
  const MemDPow bPow(b, n);
  coeff = std::vector<double>(n + 1, 0);
  for (std::size_t i = 0; i < n + 1; i++)
    coeff[i] = aPow[n - i] * bPow[i] * fac[n] / (fac[n - i] * fac[i]);
}

Polynomial::Polynomial(const std::vector<double>& coefficients)
    : coeff(coefficients) {}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
  if (rhs.coeff.size() > coeff.size()) coeff.resize(rhs.coeff.size(), 0);
  std::vector<double>::const_iterator itB = rhs.coeff.begin();
  std::vector<double>::iterator itA = coeff.begin();

  for (; itB != rhs.coeff.end(); ++itB, ++itA) *itA += *itB;

  return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
  if (rhs.coeff.size() > coeff.size()) coeff.resize(rhs.coeff.size(), 0);
  std::vector<double>::const_iterator itB = rhs.coeff.begin();
  std::vector<double>::iterator itA = coeff.begin();

  for (; itB != rhs.coeff.end(); ++itB, ++itA) *itA -= *itB;

  return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial rhs) {
  coeff.resize(rhs.coeff.size() + coeff.size() - 1);
  const std::vector<double> lhsCopy(coeff);
  coeff = std::vector<double>(lhsCopy.size(), 0);

  for (std::size_t i = 0; i < rhs.coeff.size(); i++) {
    const double& rhsVal = rhs.coeff[i];
    for (std::size_t q = 0; q < lhsCopy.size(); q++) {
      coeff[i + q] += lhsCopy[q] * rhsVal;
    }
  }

  return *this;
}

Polynomial& Polynomial::operator*=(const double rhs) {
  for (double& c : coeff) c *= rhs;

  return *this;
}

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
  lhs += rhs;
  return lhs;
}

Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
  lhs -= rhs;
  return lhs;
}

Polynomial operator*(Polynomial lhs, const Polynomial& rhs) {
  lhs *= rhs;
  return lhs;
}

Polynomial operator*(Polynomial lhs, const double rhs) {
  lhs *= rhs;
  return lhs;
}

Polynomial Polynomial::getDerivative() const {
  std::vector<double> coeffCopy(coeff);

  for (std::size_t i = 0; i < coeffCopy.size(); i++) coeffCopy[i] *= i;

  coeffCopy.erase(coeffCopy.begin());
  return Polynomial(coeffCopy);
}

Polynomial Polynomial::getIntegral() const {
  std::vector<double> coeffCopy(coeff);

  for (std::size_t i = 0; i < coeffCopy.size(); i++) coeffCopy[i] /= (i + 1);

  coeffCopy.insert(coeffCopy.begin(), 0);
  return Polynomial(coeffCopy);
}
double Polynomial::eval(const double x) const {
  double sum = 0, xi = 1;
  for (const double& c : coeff) {
    sum += c * xi;
    xi *= x;
  }
  return sum;
}

void Polynomial::printCoeff() {
  for (const double& c : coeff) std::cout << c << "\n";
}

#endif /* Polynomial_h */

//
//  FinalConcentrations.h
//  quickval2
//
//  Created by sergio saldana on 29/04/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef FinalConcentrations_h
#define FinalConcentrations_h

#include <array>
#include <cmath>

inline double helperIndividualDerivative(const double x,
                                         const double concentration,
                                         const int coefficient) {
  return (x / abs(x)) * coefficient * pow(concentration + x, coefficient - 1);
}

double helperDerivative(const std::array<double, 3>& concentrations,
                        const std::array<int, 3>& coefficients,
                        const double x) {
  double derivative0 =
             helperIndividualDerivative(-x, concentrations[0], coefficients[0]),
         derivative1 =
             helperIndividualDerivative(x, concentrations[1], coefficients[1]),
         derivative2 =
             helperIndividualDerivative(x, concentrations[2], coefficients[2]),
         value0 = coefficients[0] * pow(concentrations[0] - x, coefficients[0]),
         value1 = coefficients[1] * pow(concentrations[1] + x, coefficients[1]),
         value2 = coefficients[2] * pow(concentrations[2] + x, coefficients[2]);

  return (value0 * (derivative1 * value2 + derivative2 * value1) -
          derivative0 * value1 * value2) /
         (value0 * value0);
}

double f(const std::array<double, 3>& concentrations,
         const std::array<int, 3>& coefficients, const double k,
         const double x) {
  double value0 = coefficients[0] * pow(concentrations[0] - x, coefficients[0]),
         value1 = coefficients[1] * pow(concentrations[1] + x, coefficients[1]),
         value2 = coefficients[2] * pow(concentrations[2] + x, coefficients[2]);

  return value1 * value2 / value0 - k;
}

std::array<double, 3> finalConcentrations(
    const std::array<double, 3>& concentrations,
    const std::array<int, 3>& coefficients, const double k,
    const std::size_t&& iterations = 30) {
  double x = concentrations[0] * 0.99;
  for (std::size_t i = 0; i < iterations; i++)
    x = x - f(concentrations, coefficients, k, x) /
                helperDerivative(concentrations, coefficients, x);

  // std::cout << "newton-rapson result: " << x << "\n";

  return std::array<double, 3>{concentrations[0] - x, concentrations[1] + x,
                               concentrations[2] + x};
}

#endif /* FinalConcentrations_h */

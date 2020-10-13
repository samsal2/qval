//
//  FinalConcentrationCli.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef FinalConcentrationCli_h
#define FinalConcentrationCli_h

#include "FinalConcentrations.h"

void finalConcentrationsCli() {
  std::vector<std::pair<int, double>> reacData, prodData;
  int tempCoeff;
  for (;;) {
    tempCoeff = getInput<int>("react coeff: ");
    if (tempCoeff <= 0) break;
    reacData.push_back({tempCoeff, getInput<double>("react n: ")});
  }

  std::cout << "\nnoted\n";

  for (;;) {
    tempCoeff = getInput<int>("react coeff: ");
    if (tempCoeff <= 0) break;
    prodData.push_back({tempCoeff, getInput<double>("react n: ")});
  }
  std::pair<std::vector<double>, std::vector<double>> result =
      finalConcentrations(reacData, prodData, getInput<double>("k"));
  for (const auto& c : result.first) std::cout << c << ", ";
  std::cout << " <-> ";
  for (const auto& c : result.second) std::cout << c << ", ";
  std::cout << "\n\n";
}

#endif /* FinalConcentrationCli_h */

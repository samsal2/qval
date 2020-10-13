//
//  EDTA.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef EDTA_h
#define EDTA_h

#include <array>

#include "FinalConcentrations.h"
#include "TitrationData.h"

const std::array<double, 15> aY4 = {1.3e-23, 1.9e-18, 3.3e-14, 2.6e-11, 3.8e-9,
                                    3.7e-7,  2.3e-5,  5e-4,    5.6e-3,  5.4e-2,
                                    0.36,    0.85,    0.98,    1,       1};

class EDTA {
 public:
  EDTA(const double valorantConcentration, const double metalConcentration,
       const double V0, const int pH, const double kF);
  /*
  void setAnalyteConcentration(const double analyteConcentration);
  void setValorantConcentration(const double analyteConcentration);
  void setEquilibriumConstant(const double equilibriumConstant);
  void setStartingVolume(const double startingVolume);
  */

  const double& getVe() const { return vE; }
  double getPIon(const double V) const;

  static const double minmax;

 private:
  double valC, anC, k, v0, vE, pIon0, pIonEq;
  inline double getPIonBeforeVe(const double V) const;
  double getPIonAfterVe(const double V) const;
  void printDescription();
};

const double EDTA::minmax = TitrationData::minmax;

EDTA::EDTA(const double valorantConcentration, const double metalConcentration,
           const double V0, const int pH, const double kF)
    : anC(metalConcentration),
      valC(valorantConcentration),
      v0(V0),
      k(aY4.at(pH) * kF),
      vE(v0 * anC / valC) {
  pIon0 = -log10(anC);
  pIonEq = -log10(
      finalConcentrations({{1, 0}, {1, 0}}, {{1, anC * v0 / (v0 + vE)}}, k)
          .first[0]);
}

inline double EDTA::getPIonBeforeVe(const double V) const {
  return -log10((vE - V) * anC * v0 / ((v0 + V) * vE));
}

double EDTA::getPIonAfterVe(const double V) const {
  double excessEDTA = valC * (V - vE) / (v0 + V);
  double dilIonY = anC * v0 / (v0 + V);
  return -log10(dilIonY / (excessEDTA * k));
}

double EDTA::getPIon(const double V) const {
  if (V == 0) return pIon0;
  if (V > vE - minmax && V < vE + minmax) return pIonEq;
  if (V < vE) return getPIonBeforeVe(V);
  if (V > vE) return getPIonAfterVe(V);
  return nan("");
}

#endif /* EDTA_h */

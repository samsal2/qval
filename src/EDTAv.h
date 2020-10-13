//
//  EDTAv.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef EDTAv_h
#define EDTAv_h

#include <unordered_map>

#include "FinalConcentrations.h"
#include "TitrationData.h"

class EDTAv {
 public:
  EDTAv(const double startingEDTAConcentration, const double metalConcentration,
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

const double EDTAv::minmax = TitrationData::minmax;

EDTAv::EDTAv(const double startingEDTAConcentration,
             const double metalConcentration, const double V0, const int pH,
             const double kF)
    : anC(startingEDTAConcentration),
      valC(metalConcentration),
      v0(V0),
      k(aY4.at(pH) * kF),
      vE(v0 * anC / valC) {
  pIon0 = nan("");
  pIonEq = -log10(
      finalConcentrations({{1, 0}, {1, 0}}, {{1, anC * v0 / (v0 + vE)}}, k)
          .first[0]);
}

inline double EDTAv::getPIonAfterVe(const double V) const {
  return -log10((V - vE) * valC / (v0 + V));
}

double EDTAv::getPIonBeforeVe(const double V) const {
  double excessEDTA = (vE - V) * anC * v0 / (vE * (v0 + V));
  double dilIonY = V * anC * v0 / (vE * (v0 + V));
  return -log10(dilIonY / (excessEDTA * k));
}

double EDTAv::getPIon(const double V) const {
  if (V == 0) return pIon0;
  if (V > vE - minmax && V < vE + minmax) return pIonEq;
  if (V < vE) return getPIonBeforeVe(V);
  if (V > vE) return getPIonAfterVe(V);
  return nan("");
}

#endif /* EDTAv_h */

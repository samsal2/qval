//
//  StrongAcidStrongBase.h
//  quickval3
//
//  Created by sergio saldana on 08/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef StrongAcidStrongBase_h
#define StrongAcidStrongBase_h

#include "TitrationData.h"

class StrongAcidStrongBase : public TitrationData {
 public:
  StrongAcidStrongBase(const double analyteConcentration,
                       const double valorantConcentration, const double V0);

  void setAnalyteConcentration(const double analyteConcentration);
  void setValorantConcentration(const double valorantConcentration);
  void setStartingVolume(const double startingVolume);
  void setEquilibriumConstant(const double V) { return; }
  double getpH(const double V);

 private:
  inline double getpHBeforeVe(const double V) const;
  inline double getpHAfterVe(const double V) const;
};

StrongAcidStrongBase::StrongAcidStrongBase(const double analyteConcentration,
                                           const double valorantConcentration,
                                           const double V0)
    : TitrationData(valorantConcentration, analyteConcentration, V0) {
  pH0 = -log10(anC);
  pHeq = 7;
}

void StrongAcidStrongBase::setAnalyteConcentration(
    const double analyteConcentration) {
  anC = analyteConcentration;
  vE = v0 * anC / valC;
  pH0 = -log10(anC);
}

void StrongAcidStrongBase::setValorantConcentration(
    const double valorantConcentration) {
  valC = valorantConcentration;
  vE = v0 * anC / valC;
}

void StrongAcidStrongBase::setStartingVolume(const double startingVolume) {
  v0 = startingVolume;
  vE = vE = v0 * anC / valC;
}

inline double StrongAcidStrongBase::getpHBeforeVe(const double V) const {
  return -log10((vE - V) * anC * v0 / (vE * (v0 + V)));
}

inline double StrongAcidStrongBase::getpHAfterVe(const double V) const {
  return 14 + log10(valC * (V - vE) / (v0 + V));
}

double StrongAcidStrongBase::getpH(const double V) {
  if (V == 0) return pH0;
  if (V < vE) return getpHBeforeVe(V);
  if (V > vE - minmax && V < vE + minmax) return pHeq;
  if (V > vE) return getpHAfterVe(V);
  return nan("");
}

#endif /* StrongAcidStrongBase_h */

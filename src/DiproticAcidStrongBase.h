//
//  DiproticAcidStrongBase.h
//  quickval3
//
//  Created by sergio saldana on 08/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef DiproticAcidStrongBase_h
#define DiproticAcidStrongBase_h

#include "FinalConcentrations.h"
#include "HendersonHasselbach.h"
#include "TitrationData.h"

class DiproticAcidStrongBase : public TitrationData {
 public:
  DiproticAcidStrongBase(const double valorantConcentration,
                         const double analyteConcentration, const double V0,
                         const double kA, const double kA2);

  void setAnalyteConcentration(const double analyteConcentration);
  void setValorantConcentration(const double analyteConcentration);
  void setEquilibriumConstant(const double equilibriumConstant);
  void setEquilibriumConstant2(const double equilibriumConstant);
  void setStartingVolume(const double startingVolume);

  double getpH(const double V) const;

 private:
  double k2, kB1, kB2, vE2, pHeq2;
  inline double getpHBeforeVe(const double V) const;
  inline double getpHBeforeVe2(const double V) const;
  inline double getpHAfterVe(const double V) const;
};

DiproticAcidStrongBase::DiproticAcidStrongBase(
    const double valorantConcentration, const double analyteConcentration,
    const double V0, const double kA, const double kA2)
    : TitrationData(valorantConcentration, analyteConcentration, V0, kA),
      k2(kA2),
      kB1(1e-14 / k),
      kB2(1e-14 / kA2),
      vE2(vE * 2) {
  pH0 = -log10(finalConcentrations({{1, anC}}, {{1, 0}, {1, 0}}, k).second[0]);
  pHeq = [&]() {
    double F = anC * (v0 / (v0 + vE));
    return -log10(sqrt((k * k2 * F + k * 1e-14) / (k + F)));
  }();
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

void DiproticAcidStrongBase::setStartingVolume(const double startingVolume) {
  v0 = startingVolume;
  vE = v0 * anC / valC;
  vE2 = vE * 2;
  pHeq = [&]() {
    double F = anC * (v0 / (v0 + vE));
    return -log10(sqrt((k * k2 * F + k * 1e-14) / (k + F)));
  }();
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

void DiproticAcidStrongBase::setAnalyteConcentration(
    const double analyteConcentration) {
  anC = analyteConcentration;
  vE = v0 * anC / valC;
  vE2 = vE * 2;
  pH0 = -log10(finalConcentrations({{1, anC}}, {{1, 0}}, k).second[0]);
  pHeq = [&]() {
    double F = anC * (v0 / (v0 + vE));
    return -log10(sqrt((k * k2 * F + k * 1e-14) / (k + F)));
  }();
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

void DiproticAcidStrongBase::setValorantConcentration(
    const double valorantConcentration) {
  valC = valorantConcentration;
  vE = vE = v0 * anC / valC;
  vE2 = vE * 2;
  pHeq = [&]() {
    double F = anC * (v0 / (v0 + vE));
    return -log10(sqrt((k * k2 * F + k * 1e-14) / (k + F)));
  }();
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

void DiproticAcidStrongBase::setEquilibriumConstant(
    const double equilibriumConstant) {
  k = equilibriumConstant;
  kB1 = 1e-14 / k;
  pH0 = -log10(finalConcentrations({{1, anC}}, {{1, 0}, {1, 0}}, k).second[0]);
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

void DiproticAcidStrongBase::setEquilibriumConstant2(
    const double equilibriumConstant) {
  k2 = equilibriumConstant;
  kB2 = 1e-14 / k2;
  pHeq2 = 14 + log10(finalConcentrations({{1, anC * v0 / (v0 + vE2)}},
                                         {{1, 0}, {1, 0}}, kB2)
                         .second[0]);
}

inline double DiproticAcidStrongBase::getpHBeforeVe(const double V) const {
  return hendersonHasselbach(k, V, vE - V);
}

inline double DiproticAcidStrongBase::getpHBeforeVe2(const double V) const {
  return hendersonHasselbach(k2, V - vE, vE2 - V);
}

inline double DiproticAcidStrongBase::getpHAfterVe(const double V) const {
  return 14 + log10(valC * (V - vE2) / (v0 + V));
}

double DiproticAcidStrongBase::getpH(const double V) const {
  if (V == 0) return pH0;
  if (V > vE - minmax && V < vE + minmax) return pHeq;
  if (V > vE2 - minmax && V < vE2 + minmax) return pHeq2;
  if (V < vE) return getpHBeforeVe(V);
  if (V < vE2) return getpHBeforeVe2(V);
  if (V > vE2) return getpHAfterVe(V);
  return nan("");
}

#endif /* DiproticAcidStrongBase_h */

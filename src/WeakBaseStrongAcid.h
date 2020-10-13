//
//  WeakBaseStrongAcid.h
//  quickval3
//
//  Created by sergio saldana on 08/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef WeakBaseStrongAcid_h
#define WeakBaseStrongAcid_h

#include "FinalConcentrations.h"
#include "HendersonHasselbach.h"
#include "TitrationData.h"

class WeakBaseStrongAcid : public TitrationData {
 public:
  WeakBaseStrongAcid(const double valorantConcentration,
                     const double analyteConcentration, const double kA,
                     const double V0);

  void setAnalyteConcentration(const double analyteConcentration);
  void setValorantConcentration(const double analyteConcentration);
  void setEquilibriumConstant(const double equilibriumConstant);
  void setStartingVolume(const double startingVolume);

  double getpH(const double V);

 private:
  double kB;
  inline double getpHBeforeVe(const double V) const;
  inline double getpHAfterVe(const double V) const;
};

WeakBaseStrongAcid::WeakBaseStrongAcid(const double valorantConcentration,
                                       const double analyteConcentration,
                                       const double kA, const double V0)
    : TitrationData(valorantConcentration, analyteConcentration, kA, V0),
      kB(1e-14 / k) {
  pH0 = 14 +
        log10(finalConcentrations({{1, anC}}, {{1, 0}, {1, 0}}, kB).second[0]);
  pHeq = -log10(
      finalConcentrations({{1, anC * v0 / (v0 + vE)}}, {{1, 0}, {1, 0}}, k)
          .second[0]);
}

void WeakBaseStrongAcid::setStartingVolume(const double startingVolume) {
  v0 = startingVolume;
  vE = v0 * anC / valC;
  pHeq = -log10(
      finalConcentrations({{1, anC * v0 / (v0 + vE)}}, {{1, 0}, {1, 0}}, k)
          .second[0]);
}

void WeakBaseStrongAcid::setAnalyteConcentration(
    const double analyteConcentration) {
  anC = analyteConcentration;
  vE = v0 * anC / valC;
  pH0 = 14 +
        log10(finalConcentrations({{1, anC}}, {{1, 0}, {1, 0}}, kB).second[0]);
  pHeq = -log10(
      finalConcentrations({{1, anC * v0 / (v0 + vE)}}, {{1, 0}, {1, 0}}, k)
          .second[0]);
}

void WeakBaseStrongAcid::setValorantConcentration(
    const double valorantConcentration) {
  valC = valorantConcentration;
  vE = vE = v0 * anC / valC;
  pHeq = -log10(
      finalConcentrations({{1, anC * v0 / (v0 + vE)}}, {{1, 0}, {1, 0}}, k)
          .second[0]);
}

void WeakBaseStrongAcid::setEquilibriumConstant(
    const double equilibriumConstant) {
  k = equilibriumConstant;
  kB = 1e-14 / k;
  pH0 = 14 +
        log10(finalConcentrations({{1, anC}}, {{1, 0}, {1, 0}}, kB).second[0]);
  pHeq = -log10(
      finalConcentrations({{1, anC * v0 / (v0 + vE)}}, {{1, 0}, {1, 0}}, k)
          .second[0]);
}

inline double WeakBaseStrongAcid::getpHBeforeVe(const double V) const {
  return hendersonHasselbach(k, v0 * anC - V * valC, V * valC);
}

inline double WeakBaseStrongAcid::getpHAfterVe(const double V) const {
  return -log10(valC * (V - vE) / (v0 + V));
}

double WeakBaseStrongAcid::getpH(const double V) {
  if (V == 0) return pH0;
  if (V > vE - minmax && V < vE + minmax) return pHeq;
  if (V < vE) return getpHBeforeVe(V);
  if (V > vE) return getpHAfterVe(V);
  return nan("");
}

#endif /* WeakBaseStrongAcid_h */

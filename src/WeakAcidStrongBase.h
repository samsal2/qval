//
//  WeakAcidStrongBase.h
//  quickval3
//
//  Created by sergio saldana on 08/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef WeakAcidStrongBase_h
#define WeakAcidStrongBase_h

#include "TitrationData.h"
#include "FinalConcentrations.h"
#include "HendersonHasselbach.h"

class WeakAcidStrongBase : public TitrationData
{
public:
    
    WeakAcidStrongBase(const double analyteConcentration,
                       const double valorantConcentration,
                       const double kA,
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

WeakAcidStrongBase::WeakAcidStrongBase(const double valorantConcentration,
                                       const double analyteConcentration,
                                       const double kA,
                                       const double V0) :
TitrationData(valorantConcentration, analyteConcentration, kA, V0), kB(1e-14/k)
{
    pH0 = -log10(finalConcentrations({{1, anC}}, {{1,0}, {1,0}}, k).second[0]);
    pHeq = 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]);
    std::cout << 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]) << "\n";
}

void WeakAcidStrongBase::setStartingVolume(const double startingVolume)
{
    v0 = startingVolume;
    vE = v0 * anC/valC;
    pHeq = 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]);
}

void WeakAcidStrongBase::setAnalyteConcentration(const double analyteConcentration)
{
    anC = analyteConcentration;
    vE = v0 * anC/valC;
    pH0 = -log10(finalConcentrations({{1, anC}}, {{1, 0}, {1,0}}, k).second[0]);
    pHeq = 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]);
}

void WeakAcidStrongBase::setValorantConcentration(const double valorantConcentration)
{
    valC = valorantConcentration;
    vE = vE = v0 * anC/valC;
    pHeq = 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]);
}

void WeakAcidStrongBase::setEquilibriumConstant(const double equilibriumConstant)
{
    k = equilibriumConstant;
    kB = 1e-14/k;
    pH0 = -log10(finalConcentrations({{1, anC}}, {{1, 0}}, k).second[0]);
    pHeq = 14 + log10(finalConcentrations({{1, anC * v0/(v0 + vE)}}, {{1,0}, {1,0}}, kB).second[0]);
}


inline double WeakAcidStrongBase::getpHBeforeVe(const double V) const
{
    return hendersonHasselbach(k, V, vE - V);
}

inline double WeakAcidStrongBase::getpHAfterVe(const double V) const
{
    return 14 + log10(valC * (V - vE)/(v0 + V));
}

double WeakAcidStrongBase::getpH(const double V)
{
    if(V == 0) return pH0;
    if(V > vE - minmax && V < vE + minmax) return pHeq;
    if(V < vE) return getpHBeforeVe(V);
    if(V > vE) return getpHAfterVe(V);
    return nan("");
}


#endif /* WeakAcidStrongBase_h */

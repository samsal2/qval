//
//  DibasicBaseStrongAcid.h
//  quickval3
//
//  Created by sergio saldana on 19/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef DibasicBaseStrongAcid_h
#define DibasicBaseStrongAcid_h

#include "TitrationData.h"
#include "HendersonHasselbach.h"
#include "FinalConcentrations.h"

class DibasicBaseStrongAcid : public TitrationData
{
public:
    
    DibasicBaseStrongAcid(const double valorantConcentration,
                           const double analyteConcentration,
                           const double V0,
                           const double kA,
                           const double kA2);
    
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

DibasicBaseStrongAcid::DibasicBaseStrongAcid(const double valorantConcentration,
                                               const double analyteConcentration,
                                               const double V0,
                                               const double kA,
                                               const double kA2) :
TitrationData(valorantConcentration, analyteConcentration, V0, kA),
k2(kA2), kB1(1e-14/k), kB2(1e-14/kA2), vE2(vE * 2)
{
    pH0 = 14 + log10(finalConcentrations({{1, anC}}, {{1,0}, {1,0}}, kB1).second[0]);
    pHeq = [&](){
        double F = anC * (v0/(v0 + vE));
        return -log10(sqrt((k * k2 * F + k * 1e-14)/(k2 + F)));
    }();
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1,0}, {1,0}}, k2).second[0]);
}
    
    
void DibasicBaseStrongAcid::setStartingVolume(const double startingVolume)
{
    v0 = startingVolume;
    vE = v0 * anC/valC;
    vE2 = vE * 2;
    pHeq = [&](){
        double F = anC * (v0/(v0 + vE));
        return -log10(sqrt((kB1 * kB2 * F + kB1 * 1e-14)/(kB2 + F)));
    }();
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1, 0}}, k2).second[0]);
}

void DibasicBaseStrongAcid::setAnalyteConcentration(const double analyteConcentration)
{
    anC = analyteConcentration;
    vE = v0 * anC/valC;
    vE2 = vE * 2;
    pH0 = 14 + log10(finalConcentrations({{1, anC}}, {{1, 0}}, kB1).second[0]);
    pHeq = [&](){
        double F = anC * (v0/(v0 + vE));
        return -log10(sqrt((kB1 * kB2 * F + kB1 * 1e-14)/(kB2 + F)));
    }();
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1, 0}}, k2).second[0]);
}

void DibasicBaseStrongAcid::setValorantConcentration(const double valorantConcentration)
{
    valC = valorantConcentration;
    vE = vE = v0 * anC/valC;
    vE2 = vE * 2;
    pHeq = [&](){
        double F = anC * (v0/(v0 + vE));
        return -log10(sqrt((kB1 * kB2 * F + kB1 * 1e-14)/(kB2 + F)));
    }();
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1, 0}}, k2).second[0]);
}

void DibasicBaseStrongAcid::setEquilibriumConstant(const double equilibriumConstant)
{
    k = equilibriumConstant;
    kB1 = 1e-14/k;
     pH0 = 14 + log10(finalConcentrations({{1, anC}}, {{1, 0}}, kB1).second[0]);
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1, 0}}, k2).second[0]);
}

void DibasicBaseStrongAcid::setEquilibriumConstant2(const double equilibriumConstant)
{
    k2 = equilibriumConstant;
    kB2 = 1e-14/k2;
    pHeq2 = -log10(finalConcentrations({{1, anC * v0/(v0 + vE2)}}, {{1, 0}}, k2).second[0]);
}

inline double DibasicBaseStrongAcid::getpHBeforeVe(const double V) const
{
    return hendersonHasselbach(k, vE - V, V);
}

inline double DibasicBaseStrongAcid::getpHBeforeVe2(const double V) const
{
    return hendersonHasselbach(k2, vE2 - V, V - vE);
}

inline double DibasicBaseStrongAcid::getpHAfterVe(const double V) const
{
    return -log10(valC * (V - vE2)/(v0 + V));
}

double DibasicBaseStrongAcid::getpH(const double V) const
{
    if(V == 0) return pH0;
    if(V > vE - minmax && V < vE + minmax) return pHeq;
    if(V > vE2 - minmax && V < vE2 + minmax) return pHeq2;
    if(V < vE) return getpHBeforeVe(V);
    if(V < vE2) return getpHBeforeVe2(V);
    if(V > vE2) return getpHAfterVe(V);
    return nan("");
}


#endif /* DibasicBaseStrongAcid_h */

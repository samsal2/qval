//
//  StrongBaseStrongAcid.h
//  quickval3
//
//  Created by sergio saldana on 08/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef StrongBaseStrongAcid_h
#define StrongBaseStrongAcid_h

#include "TitrationData.h"

class StrongBaseStrongAcid : public TitrationData
{
public:
    
    StrongBaseStrongAcid(const double analyteConcentration,
                         const double valorantConcentration,
                         const double V0);
    
    void setAnalyteConcentration(const double analyteConcentration);
    void setValorantConcentration(const double valorantConcentration);
    void setStartingVolume(const double startingVolume);
    void setEquilibriumConstant(const double V) {return;}
    double getpH(const double V);
    
private:
    inline double getpHBeforeVe(const double V) const;
    inline double getpHAfterVe(const double V) const;
};

StrongBaseStrongAcid::StrongBaseStrongAcid(const double analyteConcentration,
                                           const double valorantConcentration,
                                           const double V0) :
TitrationData(valorantConcentration, analyteConcentration, V0)
{
    pH0 = 14 + log10(anC);
    pHeq = 7;
}

void StrongBaseStrongAcid::setAnalyteConcentration(const double analyteConcentration)
{
    anC = analyteConcentration;
    vE = v0 * anC/valC;
    pH0 = 14 + log10(anC);
}

void StrongBaseStrongAcid::setValorantConcentration(const double valorantConcentration)
{
    valC = valorantConcentration;
    vE = v0 * anC/valC;
}

void StrongBaseStrongAcid::setStartingVolume(const double startingVolume)
{
    v0 = startingVolume;
    vE =  vE = v0 * anC/valC;
}

inline double StrongBaseStrongAcid::getpHBeforeVe(const double V) const
{
    return 14 + log10((vE - V) * anC * v0 / (vE * (v0 + V)));
}

inline double StrongBaseStrongAcid::getpHAfterVe(const double V) const
{
    return -log10(valC * (V - vE)/(v0 + V));
}

double StrongBaseStrongAcid::getpH(const double V)
{
    if(V == 0) return pH0;
    if(V < vE) return getpHBeforeVe(V);
    if(V > vE - minmax && V < vE + minmax) return pHeq;
    if(V > vE) return getpHAfterVe(V);
    return nan("");
}


#endif /* StrongBaseStrongAcid_h */

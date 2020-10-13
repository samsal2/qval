//
//  TitrationData.h
//  quickval3
//
//  Created by sergio saldana on 06/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef TitrationData_h
#define TitrationData_h

#include <cmath>

class TitrationData
{
public:
    TitrationData(const double valorantConcentration,
                  const double analyteConcentration,
                  const double startingVolume,
                  const double equilibriumConstant = nan(""));
    
    const double& getpH0() const {return pH0;}
    const double& getpHeq() const {return pHeq;}
    const double& getVe() const {return vE;}
    const double& getK() const {return k;}
    
    void printDescription();
    
    static const double minmax;
protected:
    double valC, anC, k, pK, v0, vE, pH0, pHeq;
};

const double TitrationData::minmax = 0.000000001;

TitrationData::TitrationData(const double valorantConcentration,
                             const double analyteConcentration,
                             const double startingVolume,
                             const double equilibriumConstant)
: valC(valorantConcentration), anC(analyteConcentration), v0(startingVolume),
k(equilibriumConstant), pK(-log10(k)), vE(v0 * anC/valC){}

void TitrationData::printDescription()
{
    std::cout << "anC: " << anC << " valC: " << valC << " V0: " << v0 << " k: " << k <<"\n";
}

#endif /* TitrationData_h */

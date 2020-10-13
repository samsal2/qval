//
//  EDTAr.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef EDTAr_h
#define EDTAr_h

#include <unordered_map>
#include "TitrationData.h"
#include "FinalConcentrations.h"


class EDTAr
{
public:
    EDTAr(const double startingEDTAConcentration,
          const double metalConcentration,
          const double V0);
    /*
    void setAnalyteConcentration(const double analyteConcentration);
    void setValorantConcentration(const double analyteConcentration);
    void setEquilibriumConstant(const double equilibriumConstant);
    void setStartingVolume(const double startingVolume);
    */
    
    double getPIon(const double V) const;
    
    static const double minmax;
private:
    double startingEDTAC, metalC, v0;
};

const double EDTAr::minmax = TitrationData::minmax;


EDTAr::EDTAr(const double startingEDTAConcentration,
           const double metalConcentration,
           const double V0)
: startingEDTAC(startingEDTAConcentration), metalC(metalConcentration), v0(V0){}

double EDTAr::getPIon(const double V) const
{
    double nDiff = v0 * startingEDTAC - V * metalC;
    std::cout << nDiff << "\n";
    return -log10(nDiff/v0);
    
    
}
#endif /* EDTAr_h */

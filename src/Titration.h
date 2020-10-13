//
//  Titration.h
//  quickval3
//
//  Created by sergio saldana on 06/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef Titration_h
#define Titration_h

#include <fstream>
#include <cmath>

#include "StrongBaseStrongAcid.h"
#include "StrongAcidStrongBase.h"
#include "WeakBaseStrongAcid.h"
#include "WeakAcidStrongBase.h"
#include "DiproticAcidStrongBase.h"
#include "DibasicBaseStrongAcid.h"
#include "EDTA.h"
#include "EDTAr.h"
#include "EDTAv.h"

template<class T>
struct Titration
{
    Titration();
    void cliInterface();
    T data;
};

double askForKa()
{
    const int inp = getInput<int>("1) Use Ka\n2) Use Kb\n3) Use pKa\n4) Use pKb\nselect: ");
    switch(inp)
    {
        case 1:
            return getInput<double>("equilibrium constant (Ka): ");
        case 2:
            return 1e-14/getInput<double>("equilibrium constant (Kb): ");
        case 3:
            return pow(10, - getInput<double>("pKa: "));
        case 4:
            return pow(10, getInput<double>("pKb: ") - 14);
        default:
            return nan("");
    }
}

template<class T>
void Titration<T>::cliInterface()
{
    int inp;
    localstart:
    inp = getInput<int>(std::string("1) use range\n2) get pH at V point\n") +
                        std::string("3) get pH0\n4) get pHeq\n5) get Ve\n") +
                        std::string("6) set analyte concentraion\n") +
                        std::string("7) set valorant concentraion\n") +
                        std::string("8) set equilibrium constant\n") +
                        std::string("9) set starting volume\n0) menu\nselect: "));
    switch(inp)
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            const double step = getInput<double>("step (mL): ");
            if(step <= 0)
            {
                std::cout << "invalid step\n";
                goto localstart;
            }
            const double start = getInput<double>("start (mL): ");
            const double end = getInput<double>("end (mL): ");
            std::ofstream plotdata;
            plotdata.open("PATH/TO/file.csv", std::ofstream::out | std::ofstream::trunc);
            
            for(double V = start; V <= end + step; V += step)
            {
                std::cout << "valorant (mL): " << V << " | pH: " << data.getpH(V/1000) << "\n";
                plotdata << V << "," << data.getpH(V/1000) << "\n";
            }
            
            goto localstart;
        }
        case 2:
        {
            double V = getInput<double>("amount of valorant added (mL): ");
            std::cout << "pH at " << V << " is: " << data.getpH(V/1000) << "\n";
            goto localstart;
        }
        case 3:
        {
            std::cout << "pH0 is: " << data.getpH0() << "\n";
            goto localstart;
        }
        case 4:
        {
            std::cout << "pHeq is: " << data.getpHeq() << "\n";
            goto localstart;
        }
        case 5:
        {
            std::cout << "Ve (mL) is: " << data.getVe() * 1000 << "\n";
            goto localstart;
        }
        case 6:
        {
            data.setAnalyteConcentration(getInput<double>("new analyte concentration: "));
            goto localstart;
        }
        case 7:
        {
            data.setValorantConcentration(getInput<double>("new valorant concentration: "));
            goto localstart;
        }
        case 8:
        {
            if(isnan(data.getK()))
            {
                std::cout << "cant't modify k\n";
                goto localstart;
            }
            data.setEquilibriumConstant(askForKa());
            goto localstart;
        }
        case 9:
        {
            data.setStartingVolume( getInput<double>("new starting volume (mL): ")/1000);
            goto localstart;
        }
        
        default:
            break;
    }
}

template<>
void Titration<EDTA>::cliInterface()
{
    int inp;
    localstart:
    inp = getInput<int>(std::string("1) use range\n2) get pH at V point\n") +
                        std::string("3) get Ve\nselect: "));
    switch(inp)
    {
        case 0:
            break;
        case 1:
        {
            const double step = getInput<double>("step (mL): ");
            if(step <= 0)
            {
                std::cout << "invalid step\n";
                goto localstart;
            }
            const double start = getInput<double>("start (mL): ");
            const double end = getInput<double>("end (mL): ");
            std::ofstream plotdata;
            plotdata.open("PATH/TO/file.csv", std::ofstream::out | std::ofstream::trunc);
            
            for(double V = start; V <= end + step; V += step)
            {
                std::cout << "valorant (mL): " << V << " | pIon: " << data.getPIon(V/1000) << "\n";
                plotdata << V << "," << data.getPIon(V/1000) << "\n";
            }
            
            goto localstart;
        }
        case 2:
        {
            double V = getInput<double>("amount of valorant added (mL): ");
            std::cout << "pIon at " << V << " is: " << data.getPIon(V/1000) << "\n";
            goto localstart;
        }
        case 3:
        {
            std::cout << "Ve (mL) is: " << data.getVe() * 1000 << "\n";
            goto localstart;
        }
        default:
            break;
    }
}

template<>
void Titration<EDTAv>::cliInterface()
{
    int inp;
    localstart:
    inp = getInput<int>(std::string("1) use range\n2) get pH at V point\n") +
                        std::string("3) get Ve\nselect: "));
    switch(inp)
    {
        case 0:
            break;
        case 1:
        {
            const double step = getInput<double>("step (mL): ");
            if(step <= 0)
            {
                std::cout << "invalid step\n";
                goto localstart;
            }
            const double start = getInput<double>("start (mL): ");
            const double end = getInput<double>("end (mL): ");
            std::ofstream plotdata;
            plotdata.open("PATH/TO/file.csv", std::ofstream::out | std::ofstream::trunc);
            
            for(double V = start; V <= end + step; V += step)
            {
                std::cout << "valorant (mL): " << V << " | pIon: " << data.getPIon(V/1000) << "\n";
                plotdata << V << "," << data.getPIon(V/1000) << "\n";
            }
            
            goto localstart;
        }
        case 2:
        {
            double V = getInput<double>("amount of valorant added (mL): ");
            std::cout << "pIon at " << V << " is: " << data.getPIon(V/1000) << "\n";
            goto localstart;
        }
        case 3:
        {
            std::cout << "Ve (mL) is: " << data.getVe() * 1000 << "\n";
            goto localstart;
        }
        default:
            break;
    }
}


template<>
void Titration<EDTAr>::cliInterface()
{
    int inp;
    localstart:
    inp = getInput<int>("1) use V(mL)\nselect: ");
    switch(inp)
    {
        case 0:
            break;
        case 1:
        {
            double V = getInput<double>("amount of metal added (mL): ");
            std::cout << "pIon at " << V << " is: " << data.getPIon(V/1000) << "\n";
            goto localstart;
        }
        default:
            break;
    }
}


template<>
Titration<StrongAcidStrongBase>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000){}

template<>
Titration<StrongBaseStrongAcid>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000){}

template<>
Titration<WeakAcidStrongBase>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     askForKa()){}

template<>
Titration<WeakBaseStrongAcid>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     askForKa()){}

template<>
Titration<DiproticAcidStrongBase>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     askForKa(),
     askForKa()){}

template<>
Titration<DibasicBaseStrongAcid>::Titration() :
data(getInput<double>("valorant concentration: "),
     getInput<double>("analyte concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     askForKa(),
     askForKa()){}

template<>
Titration<EDTA>::Titration() :
data(getInput<double>("EDTA concentration: "),
     getInput<double>("metal concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     getInput<int>("pH of solution: "),
     [&](){
        int tempInp = getInput<int>("1) Use Kf\n2) Use logKf\nselect: ");
        switch(tempInp)
        {
            case 1:
                return getInput<double>("Kf: ");
            case 2:
                return pow(10, getInput<double>("logKf: "));
            default:
                return nan("");
    }}()){}

template<>
Titration<EDTAr>::Titration() :
data(getInput<double>("EDTA concentration: "),
     getInput<double>("metal concentration: "),
     getInput<double>("ETDA starting volume (mL): ")/1000){}


template<>
Titration<EDTAv>::Titration() :
data(getInput<double>("EDTA concentration: "),
     getInput<double>("metal concentration: "),
     getInput<double>("starting volume (mL): ")/1000,
     getInput<int>("pH of solution: "),
     [&](){
        int tempInp = getInput<int>("1) Use Kf\n2) Use logKf\nselect: ");
        switch(tempInp)
        {
            case 1:
                return getInput<double>("Kf: ");
            case 2:
                return pow(10, getInput<double>("logKf: "));
            default:
                return nan("");
    }}()){}
#endif /* Titration_h */

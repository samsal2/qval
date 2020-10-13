//
//  main.cpp
//  quickval3
//
//  Created by sergio saldana on 06/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Polynomial.h"

template<class T>
T getInput(const std::string& input)
{
    T inp;
    std::cout << input;
    std::cin >> inp;
    return inp;
}

#include "Titration.h"
#include "StrongAcidStrongBase.h"
#include "StrongBaseStrongAcid.h"
#include "WeakAcidStrongBase.h"
#include "WeakBaseStrongAcid.h"
#include "DiproticAcidStrongBase.h"
#include "DibasicBaseStrongAcid.h"
#include "EDTA.h"
#include "EDTAr.h"
#include "FinalConcentrationCli.h"
#include "EDTAv.h"

int main(int argc, const char * argv[]) {
    const std::string&& menu =  std::string("1) strong acid strong base titration\n") +
                                std::string("2) strong base strong acid titration\n") +
                                std::string("3) weak acid strong base titration\n") +
                                std::string("4) weak base strong acid titration\n") +
                                std::string("5) diprotic acid strong base titration\n") +
                                std::string("6) dibasic base strong acid titration\n") +
                                std::string("7) EDTA\n") +
                                std::string("8) EDTAr\n") +
                                std::string("9) EDTAv\n") +
                                std::string("10) show saved\n") +
                                std::string("11) select from saved\n") +
                                std::string("12) special\n") +
                                std::string("0) exit\nselect: ");
    
    std::vector<Titration<StrongAcidStrongBase>> sasbs;
    std::vector<Titration<StrongBaseStrongAcid>> sbsas;
    std::vector<Titration<WeakBaseStrongAcid>> wbsas;
    std::vector<Titration<WeakAcidStrongBase>> wasbs;
    std::vector<Titration<DiproticAcidStrongBase>> dasbs;
    std::vector<Titration<DibasicBaseStrongAcid>> dbsas;
    std::vector<Titration<EDTA>> edtas;
    std::vector<Titration<EDTAr>> edtars;
    std::vector<Titration<EDTAv>> edtavs;
    
    int inp, i;
    menustart:
    inp = getInput<int>(menu);
    
    switch(inp)
    {
        case 1:
        {
            sasbs.push_back(Titration<StrongAcidStrongBase>());
            sasbs.back().cliInterface();
            goto menustart;
        }
        case 2:
        {
            sbsas.push_back(Titration<StrongBaseStrongAcid>());
            sbsas.back().cliInterface();
            goto menustart;
        }
        case 3:
        {
            wasbs.push_back(Titration<WeakAcidStrongBase>());
            wasbs.back().cliInterface();
            goto menustart;
        }
        case 4:
        {
            wbsas.push_back(Titration<WeakBaseStrongAcid>());
            wbsas.back().cliInterface();
            goto menustart;
        }
        case 5:
        {
            dasbs.push_back(Titration<DiproticAcidStrongBase>());
            dasbs.back().cliInterface();
            goto menustart;
        }
        case 6:
        {
            dbsas.push_back(Titration<DibasicBaseStrongAcid>());
            dbsas.back().cliInterface();
            goto menustart;
        }
        case 7:
        {
            edtas.push_back(Titration<EDTA>());
            edtas.back().cliInterface();
            goto menustart;
        }
        case 8:
        {
            edtars.push_back(Titration<EDTAr>());
            edtars.back().cliInterface();
            goto menustart;
        }
        case 9:
        {
            edtavs.push_back(Titration<EDTAv>());
            edtavs.back().cliInterface();
            goto menustart;
        }
        case 10:
        {
            std::cout << "\nsaved titrations\n";
            for(int i = 1; i < sasbs.size() + 1; i++)
            {
                std::cout << i << ") (strong acid strong base t) ";
                sasbs[i - 1].data.printDescription();
            }
            
            for(int i = 1; i < sbsas.size() + 1; i++)
            {
                std::cout << i << ") (strong base strong acid t) ";
                sbsas[i - 1].data.printDescription();
            }
            
            for(int i = 1; i < wasbs.size() + 1; i++)
            {
                std::cout << i << ") (weak acid strong base t) ";
                wasbs[i - 1].data.printDescription();
            }
            
            for(int i = 1; i < wbsas.size() + 1; i++)
            {
                std::cout << i << ") (weak base strong acid t) ";
                wbsas[i - 1].data.printDescription();
            }
            std::cout << "done!\n\n";
            
            goto menustart;
        }
        case 11:
        {
            switch(getInput<int>(std::string("1) select from (strong acid strong base t)\n") +
                                 std::string("2) select from (strong base strong acid t)\n") +
                                 std::string("3) select from (weak acid strong base t)\n") +
                                 std::string("4) select from (weak base strong acid t)\nselect: ")))
            {
                    
                case 1:
                {
                    if(i = getInput<int>("select index: ") - 1; i >= sasbs.size() || i < 0)
                    {
                        std::cout << "invalid index\n";
                        break;
                    }
                    sasbs.at(i).cliInterface();
                    break;
                }
                    
                case 2:
                {
                    if(i = getInput<int>("select index: ") - 1; i >= sbsas.size() || i < 0)
                    {
                        std::cout << "invalid index\n";
                        break;
                    }
                    sbsas.at(i).cliInterface();
                    break;
                }
                    
                case 3:
                {
                    if(i = getInput<int>("select index: ") - 1; i >= wasbs.size() || i < 0)
                    {
                        std::cout << "invalid index\n";
                        break;
                    }
                    wasbs.at(i).cliInterface();
                    break;
                }
                    
                case 4:
                {
                    if(i = getInput<int>("select index: ") - 1; i >= wbsas.size() || i < 0)
                    {
                        std::cout << "invalid index\n";
                        break;
                    }
                    wbsas.at(i).cliInterface();
                    break;
                }
                    
                default:
                    break;
            }
            goto menustart;
        }
        case 12:
        {
            finalConcentrationsCli();
            goto menustart;
        }
            
        default:
            break;
    }
    
    return 0;
}

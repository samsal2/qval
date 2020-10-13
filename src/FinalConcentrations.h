//
//  FinalConcentrations.h
//  quickval2
//
//  Created by sergio saldana on 29/04/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef FinalConcentrations_h
#define FinalConcentrations_h


#include <vector>
#include <utility>
#include <cmath>

#include "Polynomial.h"
std::pair<std::vector<double>, std::vector<double>> finalConcentrations(const std::vector<std::pair<int, double>>& reactData,
                                                                        const std::vector<std::pair<int, double>>& prodData,
                                                                        const double k,
                                                                        const std::size_t&& iterations = 30)
{
    Polynomial denominatorExpansion({k});
    Polynomial numeratorExpansion({1});
    
    for(const std::pair<int, double>& data : reactData)
        denominatorExpansion *= Polynomial(data.second, -double(data.first), data.first);
    
    for(const std::pair<int, double>& data : prodData)
        numeratorExpansion *= Polynomial(data.second, double(data.first), data.first);
    
    const Polynomial endPolynomial(denominatorExpansion - numeratorExpansion);
    const Polynomial derivPolynomial(endPolynomial.getDerivative());
    
    double x = 0;
    for(std::size_t i = 0; i < iterations; i++)
        x = x - endPolynomial.eval(x) / derivPolynomial.eval(x);
    
    std::cout << "newton-rapson result: " << x << "\n";
    
    std::vector<double> reactantsC;
    std::vector<double> productsC;
    
    reactantsC.reserve(reactData.size());
	  productsC.reserve(prodData.size());

    for(const std::pair<int, double>& data : reactData)
        reactantsC.push_back(data.second - data.first * x);
    
    for(const std::pair<int, double>& data : prodData)
        productsC.push_back(data.second + data.first * x);
    
    return std::pair<std::vector<double>, std::vector<double>>({reactantsC, productsC});
}


 
 
#endif /* FinalConcentrations_h */

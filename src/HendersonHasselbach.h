//
//  HendersonHasselbach.h
//  quickval2
//
//  Created by sergio saldana on 29/04/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef HendersonHasselbach_h
#define HendersonHasselbach_h

inline double hendersonHasselbach(const double kA,
                                  const double acidConcentration,
                                  const double baseConcentration) {
  // 4std::cout << -log10(kA) << " " <<acidConcentration << " " <<
  // baseConcentration << "\n";
  return -log10(kA) + log10(acidConcentration / baseConcentration);
}

#endif /* HendersonHasselbach_h */

//
//  MemDFac.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef MemDFac_h
#define MemDFac_h

#include <algorithm>
#include <memory>

class MemDFac {
 public:
  MemDFac(std::size_t n);
  inline const double& operator[](const std::size_t n) const;

 private:
  const std::unique_ptr<double[]> data;
};

MemDFac::MemDFac(std::size_t n)
    : data(std::make_unique<double[]>([&]() {
        n = std::max<std::size_t>(2, n + 1);
        return n;
      }())) {
  data[0] = 1;
  data[1] = 1;
  for (std::size_t i = 2; i < n; i++) data[i] = data[i - 1] * i;
}

inline const double& MemDFac::operator[](const std::size_t n) const {
  return data[n];
}
#endif /* MemDFac_h */

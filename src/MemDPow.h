//
//  MemDPow.h
//  quickval3
//
//  Created by sergio saldana on 15/05/20.
//  Copyright © 2020 sergio saldana. All rights reserved.
//

#ifndef MemDPow_h
#define MemDPow_h

#include <memory>

class MemDPow {
 public:
  MemDPow(const double base, const std::size_t n);
  inline const double& operator[](const std::size_t n) const;

 private:
  const std::unique_ptr<double[]> data;
};

MemDPow::MemDPow(const double base, const std::size_t n)
    : data(std::make_unique<double[]>(n + 1)) {
  data[0] = 1;
  for (std::size_t i = 1; i < n + 1; i++) data[i] = data[i - 1] * base;
}

inline const double& MemDPow::operator[](const std::size_t n) const {
  return data[n];
}

#endif /* MemDPow_h */

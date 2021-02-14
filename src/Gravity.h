//
// Created by vixu on 1/7/21.
//

#ifndef SCRATCHTRIS_GRAVITY_H
#define SCRATCHTRIS_GRAVITY_H

#include <cstdint>

class Gravity {
 public:
  void addClears(uint32_t count);

  [[nodiscard]] auto getTickTime() const -> double;

 private:
  double tickTime_ = 1.0;
  uint32_t clearsCounter_ = 0;
};

#endif  // SCRATCHTRIS_GRAVITY_H
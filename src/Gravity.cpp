//
// Created by vixu on 1/7/21.
//

#include "Gravity.h"

auto Gravity::getTickTime() const -> double { return tickTime_; }

void Gravity::addClears(uint32_t count) {
  clearsCounter_ += count;
  if(clearsCounter_ >= 10) {
    clearsCounter_ -= 10;
    tickTime_ *= 0.9;
  }
}

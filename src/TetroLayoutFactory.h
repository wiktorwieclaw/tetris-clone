//
// Created by vixu on 1/7/21.
//

#ifndef SCRATCHTRIS_TETROLAYOUTFACTORY_H
#define SCRATCHTRIS_TETROLAYOUTFACTORY_H

#include <array>
#include <bitset>

#include "TetroType.h"
#include "utils.h"

class TetroLayoutFactory {
 public:
  static auto get(TetroType type) -> const std::bitset<4 * 4>& {
    return layouts_[toUnderlying(type)];
  }

  static constexpr std::array<std::bitset<4 * 4>, 7> layouts_{
      0b0000'0100'0110'0010, // Z
      0b0000'0010'0110'0100, // S
      0b0000'0010'0110'0010, // T
      0b0100'0100'0100'0100, // I
      0b0000'0110'0100'0100, // L
      0b0000'0110'0010'0010, // J
      0b0000'0110'0110'0000, // O
  };
};

#endif  // SCRATCHTRIS_TETROLAYOUTFACTORY_H

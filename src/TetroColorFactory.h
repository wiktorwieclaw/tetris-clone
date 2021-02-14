//
// Created by vixu on 1/7/21.
//

#ifndef SCRATCHTRIS_TETROCOLORFACTORY_H
#define SCRATCHTRIS_TETROCOLORFACTORY_H

#include <gxng_math.h>

#include "TetroType.h"
#include "utils.h"

class TetroColorFactory {
 public:
  static auto get(TetroType type) -> const gxng::Vec3f& {
    return colors_[toUnderlying(type)];
  }

 private:
  static constexpr std::array<gxng::Vec3f, 7> colors_{
      gxng::Vec3f{1.0f, 0.0f, 0.0f}, // Z
      gxng::Vec3f{0.0f, 1.0f, 0.0f}, // S
      gxng::Vec3f{0.8f, 0.0f, 1.0f}, // T
      gxng::Vec3f{0.0f, 1.0f, 1.0f}, // I
      gxng::Vec3f{1.0f, 0.4f, 0.0f}, // L
      gxng::Vec3f{0.0f, 0.4f, 1.0f}, // J
      gxng::Vec3f{1.0f, 1.0f, 0.0f}, // O
  };
};

#endif  // SCRATCHTRIS_TETROCOLORFACTORY_H

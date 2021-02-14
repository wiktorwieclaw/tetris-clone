//
// Created by Vixu on 18/01/2021.
//

#include "CollisionDetector.h"

auto CollisionDetector::isCollision(
    const Tetromino& tetromino, const FramedGrid& grid) -> bool {
  const auto& position = tetromino.getPosition();

  for (uint16_t j = 0; j < 4; ++j) {
    for (uint16_t i = 0; i < 4; ++i) {
      const auto x = position[0] + i + 1;
      const auto y = position[1] + j + 1;

      if (grid.read(x, y) != '-' && tetromino.readLayout(i, j)) {
        return true;
      }
    }
  }

  return false;
}


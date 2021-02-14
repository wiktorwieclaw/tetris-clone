//
// Created by Vixu on 18/01/2021.
//

#ifndef TETRIS_CLONE_COLLISIONDETECTOR_H
#define TETRIS_CLONE_COLLISIONDETECTOR_H

#include "FramedGrid.h"
#include "Tetromino.h"

class CollisionDetector {
 public:
  [[nodiscard]] static auto isCollision(
      const Tetromino& tetromino, const FramedGrid& grid) -> bool;
};

#endif  // TETRIS_CLONE_COLLISIONDETECTOR_H

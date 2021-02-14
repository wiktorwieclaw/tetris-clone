//
// Created by vixu on 5/28/20.
//

#ifndef BOGTRIS_BLOCK_H
#define BOGTRIS_BLOCK_H

#include <gxng_math.h>

#include <bitset>

#include "TetroType.h"

class FramedGrid;

class Tetromino {
 public:
  Tetromino(TetroType type, const gxng::Vec2i& position);

  [[nodiscard]] auto readLayout(uint16_t x, uint16_t y) const -> bool;

  [[nodiscard]] auto getType() const noexcept -> TetroType;

  [[nodiscard]] auto getPosition() const noexcept -> gxng::Vec2i;

  void setPosition(const gxng::Vec2i& position) noexcept;

  auto tryToMove(const FramedGrid& grid, int32_t x, int32_t y) -> bool;

  auto tryToRotateRight(const FramedGrid& grid) -> bool;

  auto tryToRotateLeft(const FramedGrid& grid) -> bool;

 private:
  void rotateRight();

  void rotateLeft();

  [[nodiscard]] auto tryToFit(const FramedGrid& grid) -> bool;

 private:
  const TetroType type_;
  std::bitset<4 * 4> layout_;
  gxng::Vec2i position_;
};

#endif  // BOGTRIS_BLOCK_H

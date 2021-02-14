//
// Created by vixu on 1/7/21.
//
#ifndef SCRATCHTRIS_FRAMEDGRID_H
#define SCRATCHTRIS_FRAMEDGRID_H

#include <gxng_math.h>

#include <cstddef>

#include "Tetromino.h"

class FramedGrid {
 public:
  FramedGrid() noexcept;

  [[nodiscard]] auto width() const noexcept -> uint16_t;

  [[nodiscard]] auto height() const noexcept -> uint16_t;

  [[nodiscard]] auto read(int16_t x, int16_t y) const noexcept -> char;

  void write(int16_t x, int16_t y, char value) noexcept;

  void write(const Tetromino& tetromino);

  auto clearAndMoveRows() -> uint16_t;

 private:
  [[nodiscard]] auto isRowFull(uint16_t rowIndex) const -> bool;

  void moveRowsDown(uint16_t lowestRowIndex);

 private:
  static constexpr uint16_t width_  = 12;
  static constexpr uint16_t height_ = 24;
  std::array<char, width_ * height_> array_;
};

#endif  // SCRATCHTRIS_FRAMEDGRID_H

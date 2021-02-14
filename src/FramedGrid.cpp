//
// Created by vixu on 1/7/21.
//

#include "FramedGrid.h"

#include "utils.h"

FramedGrid::FramedGrid() noexcept : array_{} {
  array_.fill('-');
  for (uint16_t i = 0; i < width_; ++i) {
    array_[i] = '*';
  }
  for (uint16_t i = 0; i < width_; ++i) {
    array_[i + width_ * (height_ - 1)] = '*';
  }
  for (uint16_t i = 0; i < height_; ++i) {
    array_[width_ * i] = '*';
  }
  for (uint16_t i = 0; i < height_; ++i) {
    array_[width_ - 1 + width_ * i] = '*';
  }
}

auto FramedGrid::read(int16_t x, int16_t y) const noexcept -> char {
  return array_[x + y * width_];
}

void FramedGrid::write(int16_t x, int16_t y, char value) noexcept {
  array_[x + y * width_] = value;
}

auto FramedGrid::isRowFull(uint16_t rowIndex) const -> bool {
  for (uint16_t i = width_ - 2; i > 0; --i) {
    if (read(i, rowIndex) == '-') {
      return false;
    }
  }
  return true;
}

void FramedGrid::moveRowsDown(uint16_t lowestRowIndex) {
  for (uint16_t j = lowestRowIndex; j > 1; --j) {
    for (uint16_t i = width_ - 2; i > 0; --i) {
      write(i, j, read(i, j - 1));
    }
  }

  for (uint16_t i = width_ - 2; i > 0; --i) {
    write(i, 1, '-');
  }
}

auto FramedGrid::clearAndMoveRows() -> uint16_t {
  uint16_t clearedRowsCounter = 0;
  const auto start = height_ - 2;

  for (uint16_t i = start; i > 0; --i) {
    if (isRowFull(i)) {
      clearedRowsCounter++;
      moveRowsDown(i);
      i = start + 1;
    }
  }
  return clearedRowsCounter;
}

void FramedGrid::write(const Tetromino& tetromino) {
  const auto& position = tetromino.getPosition();
  const auto symbol    = intToChar(toUnderlying(tetromino.getType()));

  for (uint16_t j = 0; j < 4; ++j) {
    for (uint16_t i = 0; i < 4; ++i) {
      if (tetromino.readLayout(i, j)) {
        const auto x = position[0] + i + 1;
        const auto y = position[1] + j + 1;

        write(x, y, symbol);
      }
    }
  }
}

auto FramedGrid::width() const noexcept -> uint16_t { return width_; }

auto FramedGrid::height() const noexcept -> uint16_t { return height_; }

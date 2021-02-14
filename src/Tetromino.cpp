//
// Created by vixu on 5/28/20.
//

#include "Tetromino.h"

#include <stdexcept>

#include "CollisionDetector.h"
#include "TetroLayoutFactory.h"

Tetromino::Tetromino(TetroType type, const gxng::Vec2i& position)
    : type_{type},
      position_{position},
      layout_{TetroLayoutFactory::get(type)} {}

auto Tetromino::readLayout(uint16_t x, uint16_t y) const -> bool {
  return layout_[x + y * 4];
}

auto Tetromino::getType() const noexcept -> TetroType { return type_; }

auto Tetromino::getPosition() const noexcept -> gxng::Vec2i {
  return position_;
}

void Tetromino::setPosition(const gxng::Vec2i& position) noexcept {
  position_ = position;
}

auto Tetromino::tryToMove(const FramedGrid& grid, int32_t x, int32_t y)
    -> bool {
  auto shift = gxng::Vec2i{x, -y};
  position_ += shift;

  if(CollisionDetector::isCollision(*this, grid)) {
    position_ -= shift;
    return false;
  }
  return true;
}

void Tetromino::rotateRight() {
  auto tempLayout = layout_;
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 4; ++i) {
      layout_[i + j * 4] = tempLayout[12 + j - (i * 4)];
    }
  }
}

void Tetromino::rotateLeft() {
  auto tempLayout = layout_;
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 4; ++i) {
      layout_[i + j * 4] = tempLayout[3 - j + (i * 4)];
    }
  }
}

auto Tetromino::tryToRotateRight(const FramedGrid& grid) -> bool {
  rotateRight();
  if (!tryToFit(grid)) {
    rotateLeft();
    return false;
  }
  return true;
}

auto Tetromino::tryToRotateLeft(const FramedGrid& grid) -> bool {
  rotateLeft();
  if (!tryToFit(grid)) {
    rotateRight();
    return false;
  }
  return true;
}

auto Tetromino::tryToFit(const FramedGrid& grid) -> bool {
  auto shift = 1;
  if (type_ == TetroType::TypeI) {
    shift = 2;
  }

  if (!CollisionDetector::isCollision(*this, grid)) {
    return true;
  }

  position_ += gxng::Vec2i{-shift, 0};

  if (!CollisionDetector::isCollision(*this, grid)) {
    return true;
  }

  position_ += gxng::Vec2i{shift * 2, 0};

  if (!CollisionDetector::isCollision(*this, grid)) {
    return true;
  }

  position_ += gxng::Vec2i{-shift, 0};

  return false;
}

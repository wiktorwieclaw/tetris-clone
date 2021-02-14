//
// Created by vixu on 1/16/21.
//

#include "Button.h"

#include "utils.h"

Button::Button(const gxng::Vec2f& position, const gxng::Vec2f& size)
    : position_{position}, size_{size} {}

auto Button::getSize() const -> const gxng::Vec2f& { return size_; }

void Button::setSize(const gxng::Vec2f& size) { size_ = size; }

auto Button::getPosition() const -> const gxng::Vec2f& { return position_; }

void Button::setPosition(const gxng::Vec2f& position) { position_ = position; }

auto Button::isClicked(double x, double y) const -> bool {
  bool xInRange = x >= position_[0] && x <= position_[0] + size_[0];
  bool yInRange = y >= position_[1] && y <= position_[1] + size_[1];

  return xInRange && yInRange;
}
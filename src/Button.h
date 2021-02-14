//
// Created by vixu on 1/16/21.
//

#ifndef SCRATCHTRIS_BUTTON_H
#define SCRATCHTRIS_BUTTON_H

#include <gxng_input.h>
#include <gxng_math.h>

class Button {
 public:
  Button() = default;

  Button(const gxng::Vec2f& position, const gxng::Vec2f& size);

  [[nodiscard]] auto isClicked(double x, double y) const -> bool;

  [[nodiscard]] auto getPosition() const -> const gxng::Vec2f&;

  [[nodiscard]] auto getSize() const -> const gxng::Vec2f&;

  void setPosition(const gxng::Vec2f& position);

  void setSize(const gxng::Vec2f& size);

 private:
  gxng::Vec2f position_;
  gxng::Vec2f size_;
};

#endif  // SCRATCHTRIS_BUTTON_H

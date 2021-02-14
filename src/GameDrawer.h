//
// Created by vixu on 1/7/21.
//

#ifndef SCRATCHTRIS_GAMEDRAWER_H
#define SCRATCHTRIS_GAMEDRAWER_H

#include <gxng_graphics.h>

#include "FramedGrid.h"
#include "GameLogic.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "Tetromino.h"

class GameDrawer {
 public:
  explicit GameDrawer(ResourceManager& manager);

  void drawGameplay(gxng::Renderer& renderer, const GameLogic& gameLogic);

  void drawMenu(gxng::Renderer& renderer, const GameUI& gameMenu);

  void drawPopup(gxng::Renderer& renderer);

 private:
  void drawTetromino(gxng::Renderer& renderer, TetroType type,
      gxng::Vec2f position, gxng::Vec2f tileSize);

  void drawMovingTetromino(
      gxng::Renderer& renderer, const Tetromino& tetromino);

  void drawStashedTetromino(
      gxng::Renderer& renderer, const Tetromino& tetromino);

  void drawQueue(gxng::Renderer& renderer, const std::vector<TetroType>& queue);

  void drawGrid(gxng::Renderer& renderer, const FramedGrid& grid);

  [[nodiscard]] static auto toScreenPosition(const gxng::Vec2i& onGridPosition)
      -> gxng::Vec2f;

 private:
  static constexpr gxng::Vec2f tilePixelSize_{25.0f, 25.0f};
  static constexpr gxng::Vec2f gridPosition_{275.0f, 0.0f};
  ResourceManager& resourceManager_;
};

#endif  // SCRATCHTRIS_GAMEDRAWER_H

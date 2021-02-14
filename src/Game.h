//
// Created by vixu on 5/22/20.
//

#ifndef GAMEDEMO2D_GAME_H
#define GAMEDEMO2D_GAME_H

#include <gxng_graphics.h>
#include <gxng_input.h>

#include "GameDrawer.h"
#include "GameLogic.h"
#include "GameState.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "Tetromino.h"

class Game {
 public:
  explicit Game(gxng::Window& window, ResourceManager& resourceManager);

  void run(gxng::Renderer& renderer);

 private:
  gxng::Window& window_;
  gxng::KeyInput keyInput_;
  gxng::MouseInput mouseInput_;
  GameState gameState_ = GameState::Menu;
  GameUI gameUi_;
  GameLogic gameLogic_;
  GameDrawer gameDrawer_;
};

#endif  // GAMEDEMO2D_GAME_H

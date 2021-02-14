//
// Created by vixu on 5/22/20.
//

#include "Game.h"

Game::Game(gxng::Window& window, ResourceManager& resourceManager)
    : window_{window},
      keyInput_{window_},
      mouseInput_{window_},
      gameLogic_{gameState_},
      gameDrawer_{resourceManager},
      gameUi_(gameState_) {
  keyInput_.setCallback(GameLogic::inputCallback);
  mouseInput_.setButtonCallback(GameUI::mouseInputCallback);
}

void Game::run(gxng::Renderer& renderer) {
  while (!window_.shouldClose() && gameState_ != GameState::ShouldClose) {
    window_.clear();

    if (gameState_ == GameState::Menu) {
      gameDrawer_.drawMenu(renderer, gameUi_);
    }
    else if (gameState_ == GameState::InGame) {
      gameLogic_.gameplayTick(keyInput_);
      gameDrawer_.drawGameplay(renderer, gameLogic_);
    }
    else if (gameState_ == GameState::Lost) {
      gameDrawer_.drawGameplay(renderer, gameLogic_);
      gameDrawer_.drawPopup(renderer);
    }
    else if (gameState_ == GameState::ShouldRestart) {
      gameLogic_.restart();
      gameState_ = GameState::InGame;
    }

    window_.update();
  }
}

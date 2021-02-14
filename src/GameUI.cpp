//
// Created by vixu on 1/8/21.
//

#include "GameUI.h"

GameUI* GameUI::instance_;

void GameUI::mouseInputCallback(
    double x, double y, int button, gxng::Action action) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == gxng::Action::Release) {
    if (instance_->gameState_ == GameState::Menu) {
      handleMainMenuInput(x, y);
    }
    else if (instance_->gameState_ == GameState::Lost) {
      handleLostMenuInput(x, y);
    }
    else if(instance_->gameState_ == GameState::InGame) {
      handleGameplayMenuInput(x, y);
    }
  }
}

GameUI::GameUI(GameState& gameState) : gameState_{gameState} {
  if(instance_ == nullptr) {
   instance_ = this;
  }
  else {
    throw std::runtime_error{"There can be only one GameUI object"};
  }
}

void GameUI::handleMainMenuInput(double x, double y) {
  if (instance_->startButton_.isClicked(x, y)) {
    instance_->gameState_ = GameState::ShouldRestart;
  }
  else if (instance_->exitButton_.isClicked(x, y)) {
    instance_->gameState_ = GameState::ShouldClose;
  }
}

void GameUI::handleLostMenuInput(double x, double y) {
  if (instance_->restartButton_.isClicked(x, y)) {
    instance_->gameState_ = GameState::ShouldRestart;
  }
  else if (instance_->menuButton_.isClicked(x, y)) {
    instance_->gameState_ = GameState::Menu;
  }
}

void GameUI::handleGameplayMenuInput(double x, double y) {
  if (instance_->inGameMenuButton_.isClicked(x, y)) {
    instance_->gameState_ = GameState::Menu;
  }
}

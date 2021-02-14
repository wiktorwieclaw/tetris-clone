//
// Created by vixu on 1/8/21.
//

#ifndef SCRATCHTRIS_GAMEMENU_H
#define SCRATCHTRIS_GAMEMENU_H

#include <gxng_graphics.h>
#include <gxng_input.h>

#include "Button.h"
#include "GameState.h"

class GameUI {
 public:
  explicit GameUI(GameState& gameState);

 public:
  static void mouseInputCallback(
      double x, double y, int button, gxng::Action action);

 private:
  static void handleMainMenuInput(double x, double y);
  static void handleLostMenuInput(double x, double y);
  static void handleGameplayMenuInput(double x, double y);

 private:
  static constexpr gxng::Vec2f mainMenuButtonSize_{121.0f, 64.0f};
  Button startButton_{gxng::Vec2f{209.0f, 300.0f}, mainMenuButtonSize_};
  Button exitButton_{gxng::Vec2f{470.0f, 300.0f}, mainMenuButtonSize_};

  static constexpr gxng::Vec2f popupButtonSize_{171.0f, 64.0f};
  Button restartButton_{gxng::Vec2f{159.0f, 275.0f}, popupButtonSize_};
  Button menuButton_{gxng::Vec2f{470.0f, 275.0f}, popupButtonSize_};

  Button inGameMenuButton_{gxng::Vec2f{580.0f, 491.0f}, mainMenuButtonSize_};

  GameState& gameState_;
  static GameUI* instance_;
};

#endif  // SCRATCHTRIS_GAMEMENU_H
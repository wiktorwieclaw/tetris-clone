//
// Created by vixu on 5/27/20.
//

#ifndef BOGTRIS_GRID_H
#define BOGTRIS_GRID_H

#include <gxng_graphics.h>
#include <gxng_input.h>
#include <gxng_math.h>

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "FramedGrid.h"
#include "Gravity.h"
#include "Tetromino.h"
#include "GameState.h"

class GameLogic {
 public:
  explicit GameLogic(GameState& gameState);

  void gameplayTick(const gxng::KeyInput& keyInput);

  void handleInput(const gxng::KeyInput& keyInput);

  void createNewFallingTetromino(std::vector<TetroType>& queue);

  void handleTetrominoHit();

  [[nodiscard]] auto checkIfLost() const -> bool;

  [[nodiscard]] auto getGrid() const -> const FramedGrid&;

  [[nodiscard]] auto getMovingTetromino() const -> const Tetromino*;

  [[nodiscard]] auto getQueue() const -> const std::vector<TetroType>&;

  void tryToStashTetromino();

  [[nodiscard]] auto getStashedTetromino() const -> const Tetromino*;

  void restart() noexcept;

 public:
  static void inputCallback(int key, gxng::Action action);

 private:
  [[nodiscard]] auto getRandomTetroType() const -> TetroType;

 private:
  double timeOfPreviousTick_;
  GameState& gameState_;
  FramedGrid grid_;
  bool wasStashed_ = false;
  std::unique_ptr<Tetromino> movingTetromino_;
  std::unique_ptr<Tetromino> stashedTetromino_;
  std::vector<TetroType> queue_;
  Gravity gravity_;
  static GameLogic* instance_;
};

#endif  // BOGTRIS_GRID_H

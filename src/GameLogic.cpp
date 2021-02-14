//
// Created by vixu on 5/27/20.
//

#include "GameLogic.h"

#include <memory>

#include "CollisionDetector.h"
#include "utils.h"

GameLogic* GameLogic::instance_;

GameLogic::GameLogic(GameState& gameState)
    : gameState_{gameState}, timeOfPreviousTick_{} {
  if (instance_ == nullptr) {
    instance_ = this;
  }
  else {
    std::runtime_error{"There can be only one GameLogic instance"};
  }
}

void GameLogic::createNewFallingTetromino(std::vector<TetroType>& queue) {
  auto newType = queue.front();
  queue.erase(queue.begin());

  const gxng::Vec2i newPosition(grid_.width() / 2 - 3, 0);
  movingTetromino_ = std::make_unique<Tetromino>(newType, newPosition);

  queue.push_back(getRandomTetroType());
}

auto GameLogic::getGrid() const -> const FramedGrid& { return grid_; }

auto GameLogic::getMovingTetromino() const -> const Tetromino* {
  return movingTetromino_.get();
}

void GameLogic::gameplayTick(const gxng::KeyInput& keyInput) {
  auto time = glfwGetTime();

  if (time - timeOfPreviousTick_ > gravity_.getTickTime()) {
    timeOfPreviousTick_ = time;

    if (!movingTetromino_->tryToMove(grid_, 0, -1)) {
      handleTetrominoHit();
    }
  }
  handleInput(keyInput);
}

auto GameLogic::getRandomTetroType() const -> TetroType {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  static std::uniform_int_distribution<int> dist(0, 6);

  TetroType x;
  do {
    x = static_cast<TetroType>(dist(mt));
  } while (std::ranges::find(queue_, x) != queue_.end());

  return x;
}

auto GameLogic::getQueue() const -> const std::vector<TetroType>& {
  return queue_;
}

auto GameLogic::checkIfLost() const -> bool {
  for (uint16_t i = 1; i < grid_.width() - 1; ++i) {
    if (grid_.read(i, 3) != '-') {
      return true;
    }
  }
  return false;
}

void GameLogic::handleTetrominoHit() {
  grid_.write(*movingTetromino_);

  if (checkIfLost()) {
    gameState_ = GameState::Lost;
  }
  else {
    wasStashed_ = false;
    createNewFallingTetromino(queue_);
    auto count = grid_.clearAndMoveRows();
    gravity_.addClears(count);
  }
}

auto GameLogic::getStashedTetromino() const -> const Tetromino* {
  return stashedTetromino_.get();
}

void GameLogic::tryToStashTetromino() {
  auto pos = movingTetromino_->getPosition();
  if (!wasStashed_) {
    if (stashedTetromino_ != nullptr) {
      stashedTetromino_.swap(movingTetromino_);
      movingTetromino_->setPosition(pos);

      if (CollisionDetector::isCollision(*movingTetromino_, grid_)) {
        stashedTetromino_.swap(movingTetromino_);
        return;
      }
    }
    else {
      stashedTetromino_ = std::move(movingTetromino_);
      auto copy         = queue_;
      createNewFallingTetromino(queue_);
      movingTetromino_->setPosition(pos);

      if (CollisionDetector::isCollision(*movingTetromino_, grid_)) {
        queue_           = copy;
        movingTetromino_ = std::move(stashedTetromino_);
        return;
      }
    }
  }
  wasStashed_ = true;
}

void GameLogic::restart() noexcept {
  queue_.clear();
  for (uint16_t i = 0; i < 4; ++i) {
    queue_.push_back(getRandomTetroType());
  }

  gravity_            = Gravity{};
  grid_               = FramedGrid{};
  stashedTetromino_   = nullptr;
  timeOfPreviousTick_ = glfwGetTime();
  createNewFallingTetromino(queue_);
}

void GameLogic::handleInput(const gxng::KeyInput& keyInput) {
  static auto lastTimeR = 0.0;
  static auto lastTimeL = 0.0;
  static auto lastTimeD = 0.0;

  const auto time     = glfwGetTime();
  auto timeBetween    = 0.1;
  const auto tickTime = gravity_.getTickTime();
  if (tickTime < 0.1) {
    timeBetween = tickTime;
  }

  if (!(keyInput.isPressed(GLFW_KEY_RIGHT) &&
          keyInput.isPressed(GLFW_KEY_LEFT))) {
    if (keyInput.isPressed(GLFW_KEY_RIGHT) && time - lastTimeR > timeBetween) {
      lastTimeR = time;
      movingTetromino_->tryToMove(grid_, 1, 0);
    }

    if (keyInput.isPressed(GLFW_KEY_LEFT) && time - lastTimeL > timeBetween) {
      lastTimeL = time;
      movingTetromino_->tryToMove(grid_, -1, 0);
    }
  }

  if (keyInput.isPressed(GLFW_KEY_DOWN) && time - lastTimeD > timeBetween) {
    timeOfPreviousTick_ = time;
    lastTimeD           = time;

    if (!movingTetromino_->tryToMove(grid_, 0, -1)) {
      handleTetrominoHit();
    }
  }
}

void GameLogic::inputCallback(int key, gxng::Action action) {
  if (instance_->gameState_ != GameState::InGame) return;
  const auto& grid = instance_->grid_;
  if (key == GLFW_KEY_UP && action == gxng::Action::Press) {
    while (instance_->movingTetromino_->tryToMove(grid, 0, -1)) {
    }
    instance_->handleTetrominoHit();
  }

  if (key == GLFW_KEY_Z && action == gxng::Action::Press) {
    instance_->movingTetromino_->tryToRotateLeft(grid);
  }

  if (key == GLFW_KEY_X && action == gxng::Action::Press) {
    instance_->movingTetromino_->tryToRotateRight(grid);
  }

  if (key == GLFW_KEY_LEFT_SHIFT && action == gxng::Action::Press) {
    instance_->tryToStashTetromino();
  }
}
//
// Created by vixu on 1/7/21.
//

#include "GameDrawer.h"

#include "TetroColorFactory.h"
#include "TetroLayoutFactory.h"

GameDrawer::GameDrawer(ResourceManager& manager) : resourceManager_{manager} {
  const gxng::Mat4x4f projection =
      gxng::makeOrthographicMatrix(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  auto& shader = manager.getShader("basic");
  gxng::AutoBinder shaderBinder{shader};
  shader.setUniformMat4x4f("projection", projection);
}

void GameDrawer::drawGameplay(
    gxng::Renderer& renderer, const GameLogic& gameLogic) {
  renderer.draw(gxng::Vec2f{0.0f, 0.0f}, gxng::Vec2f{800.0f, 600.0f}, 0.0f,
      gxng::Vec3f{1.0f, 1.0f, 1.0f}, resourceManager_.getTexture("background"));

  drawGrid(renderer, gameLogic.getGrid());
  drawMovingTetromino(renderer, *gameLogic.getMovingTetromino());
  drawQueue(renderer, gameLogic.getQueue());
  const auto* stashed = gameLogic.getStashedTetromino();

  if (stashed != nullptr) {
    drawStashedTetromino(renderer, *stashed);
  }
}

void GameDrawer::drawMovingTetromino(
    gxng::Renderer& renderer, const Tetromino& tetromino) {
  auto color = (TetroColorFactory::get(tetromino.getType()));

  for (uint16_t i = 0; i < 4; ++i) {
    for (uint16_t j = 0; j < 4; ++j) {
      const auto position         = tetromino.getPosition() + gxng::Vec2i{i, j};
      const bool isBelowSecondRow = position[1] >= 2;

      if (isBelowSecondRow && tetromino.readLayout(i, j)) {
        auto pos = toScreenPosition(position);

        renderer.draw(pos, tilePixelSize_, 0.0f, color,
            resourceManager_.getTexture("tile"));
      }
    }
  }
}

auto GameDrawer::toScreenPosition(const gxng::Vec2i& onGridPosition)
    -> gxng::Vec2f {
  const auto onGridPositionFloat = static_cast<gxng::Vec2f>(onGridPosition);
  return gridPosition_ + tilePixelSize_ * onGridPositionFloat;
}

void GameDrawer::drawMenu(gxng::Renderer& renderer, const GameUI& gameMenu) {
  renderer.draw(gxng::Vec2f{0.0f, 0.0f}, gxng::Vec2f{800.0f, 600.0f}, 0.0f,
      gxng::Vec3f{1.0f, 1.0f, 1.0f}, resourceManager_.getTexture("menu"));
}

void GameDrawer::drawQueue(
    gxng::Renderer& renderer, const std::vector<TetroType>& queue) {
  gxng::Vec2f tileSize{16.0f, 16.0f};
  gxng::Vec2f startPosition{608.0f, 66.0f};
  for (auto tetroType : queue) {
    drawTetromino(renderer, tetroType, startPosition, tileSize);
    startPosition[1] += tileSize[1] * 5;
  }
}

void GameDrawer::drawStashedTetromino(
    gxng::Renderer& renderer, const Tetromino& tetromino) {
  gxng::Vec2f tileSize{16.0f, 16.0f};
  gxng::Vec2f startPosition{127.0f, 66.0f};
  const auto tetroType = tetromino.getType();

  drawTetromino(renderer, tetroType, startPosition, tileSize);
}

void GameDrawer::drawPopup(gxng::Renderer& renderer) {
  renderer.draw(gxng::Vec2f{0.0f, 0.0f}, gxng::Vec2f{800.0f, 600.0f}, 0.0f,
      gxng::Vec3f{1.0f, 1.0f, 1.0f}, resourceManager_.getTexture("lost"));
}

void GameDrawer::drawTetromino(gxng::Renderer& renderer, TetroType type,
    gxng::Vec2f position, gxng::Vec2f tileSize) {
  const auto tetrominoLayout = TetroLayoutFactory::get(type);
  const auto color           = TetroColorFactory::get(type);

  for (uint16_t i = 0; i < 4; ++i) {
    for (uint16_t j = 0; j < 4; ++j) {
      const float iFloat = i;
      const float jFloat = j;

      auto pos = position + gxng::Vec2f{iFloat, jFloat} * tileSize;

      if (type == TetroType::TypeI) {
        pos[0] -= tileSize[0];
      }

      if (tetrominoLayout[i + j * 4]) {
        renderer.draw(
            pos, tileSize, 0.0f, color, resourceManager_.getTexture("tile"));
      }
    }
  }
}

void GameDrawer::drawGrid(
    gxng::Renderer& renderer, const FramedGrid& grid) {
  for (uint16_t i = 0; i < grid.width() - 1; ++i) {
    for (uint16_t j = 2; j < grid.height() - 1; ++j) {
      char symbol = grid.read(i + 1, j + 1);

      if (symbol >= '0' && symbol <= '6') {
        const auto tetroType = TetroType{charToInt(symbol)};

        auto color = (TetroColorFactory::get(tetroType));
        auto pos   = toScreenPosition(gxng::Vec2i{i, j});

        renderer.draw(pos, tilePixelSize_, 0.0f, color,
            resourceManager_.getTexture("tile"));
      }
    }
  }
}

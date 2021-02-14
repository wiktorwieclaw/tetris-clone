#include <gxng_graphics.h>
#include "Game.h"

void loadAllTextures(ResourceManager& resourceManager) {
  resourceManager.loadTexture("tile", "textures/tile.png");
  resourceManager.loadTexture("background", "textures/background.png");
  resourceManager.loadTexture("menu", "textures/menu.png");
  resourceManager.loadTexture("lost", "textures/lost.png");
}

void loadAllShaders(ResourceManager& resourceManager) {
  resourceManager.loadShader(
      "basic", "src/shaders/basic.vert", "src/shaders/basic.frag");
}

auto main() -> int {
  gxng::Window window{800, 600, "Tetris"};
  ResourceManager resourceManager;
  loadAllTextures(resourceManager);
  loadAllShaders(resourceManager);

  Game game(window, resourceManager);
  gxng::Renderer renderer(resourceManager.getShader("basic"));

  game.run(renderer);
}

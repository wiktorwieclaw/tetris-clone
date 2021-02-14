//
// Created by vixu on 1/6/21.
//

#ifndef SCRATCHTRIS_RESOURCEMANAGER_H
#define SCRATCHTRIS_RESOURCEMANAGER_H

#include <gxng_graphics.h>

#include <string_view>
#include <unordered_map>

class ResourceManager {
 public:
  void loadTexture(std::string_view name, std::string_view path);

  void loadShader(std::string_view name, std::string_view vertexPath,
      std::string_view fragmentPath);

  auto getShader(std::string_view name) -> const gxng::Shader&;

  auto getTexture(std::string_view name) -> const gxng::Texture&;

 private:
  std::unordered_map<std::string_view, gxng::Shader> shaders_;
  std::unordered_map<std::string_view, gxng::Texture> textures_;
};

#endif  // SCRATCHTRIS_RESOURCEMANAGER_H

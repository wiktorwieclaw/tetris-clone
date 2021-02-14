//
// Created by vixu on 1/6/21.
//

#include "ResourceManager.h"

void ResourceManager::loadTexture(
    std::string_view name, std::string_view path) {
  textures_[name].loadImage(path);
}

void ResourceManager::loadShader(std::string_view name,
    std::string_view vertexPath, std::string_view fragmentPath) {
  shaders_[name].load(vertexPath, fragmentPath);
}

auto ResourceManager::getTexture(std::string_view name)
    -> const gxng::Texture& {
  if (!textures_.contains(name)) {
    throw std::runtime_error{"No texture named " + std::string{name}};
  }
  return textures_[name];
}

auto ResourceManager::getShader(std::string_view name) -> const gxng::Shader& {
  if (!shaders_.contains(name)) {
    throw std::runtime_error{"No shader named " + std::string{name}};
  }
  return shaders_[name];
}
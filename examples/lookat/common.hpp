#ifndef COMMON_HPP_
#define COMMON_HPP_

#include "abcgOpenGL.hpp"

struct Vertex {
  glm::vec3 position;

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

struct ObjectConfiguration {
  glm::vec2 startPosition;
  glm::vec3 color;
  float minHigh;
  float maxHigh;
  bool verticalRotate;
  float radiusVerticalRotate;
  float scale;
  std::string_view path;
  bool choosed;
};

#endif
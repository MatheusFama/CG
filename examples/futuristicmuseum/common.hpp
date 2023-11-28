#ifndef COMMON_HPP_
#define COMMON_HPP_

#include "abcgOpenGL.hpp"

// struct Vertex {
//   glm::vec3 position{};
//   glm::vec3 normal{};

//   friend bool operator==(Vertex const &, Vertex const &) = default;
// };

struct Vertex {
  glm::vec3 position{};
  glm::vec3 normal{};
  glm::vec2 texCoord{};
  glm::vec4 tangent{};

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

struct ObjectConfiguration {
  glm::vec2 startPosition;
  // glm::vec3 color;
  float minHigh;
  float maxHigh;
  bool verticalRotate;
  float radiusVerticalRotate;
  float scale;
  std::string path;
  bool choosed;
  float rotationSpeed;
  // float triangulesToDraw;
  std::string normalTexturepath;
  std::string difuseTexturepath;
  int mode;
};

#endif
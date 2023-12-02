#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

// #include "base.hpp"
#include "camera.hpp"
#include "collection.hpp"
#include "common.hpp"
#include "estatue.hpp"
#include "ground.hpp"
#include "wall.hpp"
#include <random>

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;
  void onUpdate() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_program{};
  GLuint base_program{};
  GLuint groundWall_program{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};

  Camera m_camera;
  float m_dollySpeed{};
  float m_truckSpeed{};
  float m_panSpeed{};

  Collection m_collection;
  Ground m_ground;
  Wall m_wall;

  std::vector<ObjectConfiguration> allConfigs;
  std::vector<glm::vec2> positions;

  std::default_random_engine m_randomEngine;
};

#endif
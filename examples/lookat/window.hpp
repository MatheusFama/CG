#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

#include "base.hpp"
#include "camera.hpp"
#include "common.hpp"
#include "estatue.hpp"
#include "ground.hpp"
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

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};

  Camera m_camera;
  float m_dollySpeed{};
  float m_truckSpeed{};
  float m_panSpeed{};

  Ground m_ground;
  Base m_base;
  Estatue m_estatue;

  // Base m_base1;
  // Estatue m_estatue1;

  std::vector<Base> m_bases;
  std::vector<Estatue> m_estatues;

  std::vector<ObjectConfiguration> allConfigs;
  std::vector<glm::vec2> positions;

  std::default_random_engine m_randomEngine;
};

#endif
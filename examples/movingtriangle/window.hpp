#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_VAO{};
  GLuint m_VBOVertices{};
  GLuint m_VBOTranslation{};
  GLuint m_program{};
  GLuint m_Lineprogram{};
  GLfloat m_translation{0.0};
  std::default_random_engine m_randomEngine;
  glm::vec2 m_P{};

  void setupModel();
};

#endif
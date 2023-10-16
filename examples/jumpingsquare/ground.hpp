#ifndef GROUND_HPP_
#define GROUND_HPP_

#include "abcgOpenGL.hpp"

class Ground {
public:
  void create(GLuint program);
  void paint();
  void destroy();

  glm::vec4 m_color{1};
  glm::vec2 position1{-1.0f, -0.02f};
  glm::vec2 position2{1.0f, -0.02f};

private:
  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};
};
#endif
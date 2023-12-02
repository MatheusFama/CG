#ifndef WALL_HPP_
#define WALL_HPP_

#include "abcgOpenGL.hpp"

class Wall {
public:
  void create(GLuint program);
  void paint(glm::mat4 viewMatrix, glm::mat4 projMatrix);
  void destroy();

private:
  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};

  GLint m_modelMatrixLoc{};
  GLint m_viewMatrixLoc{};
  GLint m_projMatrixLoc{};
  GLint m_colorLoc{};
};

#endif
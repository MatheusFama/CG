#ifndef WALL_HPP_
#define WALL_HPP_

#include "abcgOpenGL.hpp"

class Wall {
public:
  void create(GLuint program);
  void paint();
  void destroy();

private:
  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};

  GLint m_modelMatrixLoc{};
  GLint m_colorLoc{};
};

#endif
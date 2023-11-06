#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "abcgOpenGL.hpp"

class Estatue {
public:
  void create(GLuint program);
  void paint();
  void destroy();
  void update(float deltaTime);

private:
  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
};
#endif
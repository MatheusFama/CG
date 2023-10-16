#ifndef SQUARE_HPP_
#define SQUARE_HPP_

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"
#include <list>
class Square {
public:
  void create(GLuint program);
  void paint(GameData const &gameData);
  void destroy();
  void update(GameData const &gameData);
  glm::vec2 getCenter();

  GLfloat translationSpace{0.0003f};
  GLfloat m_translation{0.0};
  glm::vec4 m_color{1};
  glm::vec2 position{-0.85f, 0.03f};
  GLfloat size{0.1f};

private:
  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLint m_translationLoc{};
};
#endif
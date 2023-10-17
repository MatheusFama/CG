#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <list>
#include <random>

#include "abcgOpenGL.hpp"

#include "gamedata.hpp"
#include "square.hpp"

class Obstacles {
public:
  void create(GLuint program);
  void paint(GameData const &gameData);
  void destroy();
  void update(float deltaTime);
  abcg::Timer m_restartWaitTimer;
  GLfloat maxDistance{5.5};
  GLfloat distanceTime{3};
  struct Obstacle {
    GLuint m_VAO{};
    GLuint m_VBO{};
    GLfloat m_translation{0.0};
    bool remove{false};
    glm::vec4 m_color{1};
    glm::vec2 position{0.99f, 0.08f};
    float m_height{0.2f};
    float m_base{0.3f};
    GLfloat translationSpace{0.0001f};
    GLint m_translationLoc{};

    glm::vec2 getCenter() {
      return glm::vec2{position.x + m_translation, position.y};
    };

    void destroy() {
      abcg::glDeleteBuffers(1, &m_VBO);
      abcg::glDeleteVertexArrays(1, &m_VAO);
    };
  };

  std::list<Obstacle> m_obstacles;

  Obstacle makeObstacle();

private:
  GLuint m_program{};
};

#endif
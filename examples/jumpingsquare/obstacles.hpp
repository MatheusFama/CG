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
  void update();
  abcg::Timer m_restartWaitTimer;

  struct Obstacle {
    GLuint m_VAO{};
    GLuint m_VBO{};
    std::list<glm::vec2> m_positions;
    GLfloat m_translation{0.0};
    bool destroy{false};
    glm::vec4 m_color{1};
    glm::vec2 position{0.99f, 0.08f};
    float m_height{0.2f};
    float m_base{0.3f};
    GLfloat translationSpace{0.0001f};
    GLint m_translationLoc{};

    std::list<glm::vec2> getVertices() {
      std::list<glm::vec2> m_positionsTranslation;

      for (auto const &pos : m_positions) {
        int x = pos.x + m_translation;
        m_positionsTranslation.push_back(glm::vec2{x, pos.y});
      }

      return m_positionsTranslation;
    };

    glm::vec2 getCenter() {
      return glm::vec2{position.x + m_translation, position.y};
    };
  };

  std::list<Obstacle> m_obstacles;

  Obstacle makeObstacle();

private:
  GLuint m_program{};
  // GLint m_translationLoc{};

  std::default_random_engine m_randomEngine;
  float randomTime{0.0};
  std::uniform_real_distribution<float> m_randomDist{1.0f, 10.0f};
};

#endif
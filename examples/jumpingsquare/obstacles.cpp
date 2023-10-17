#include "obstacles.hpp"
#include <glm/gtx/fast_trigonometry.hpp>

void Obstacles::create(GLuint program) {
  destroy();

  m_program = program;

  m_obstacles.clear();
}

void Obstacles::paint(GameData const &gameData) {
  if (gameData.m_state != State::Playing)
    return;

  abcg::glUseProgram(m_program);

  for (auto const &obstacle : m_obstacles) {

    abcg::glBindVertexArray(obstacle.m_VAO);

    abcg::glUniform1f(obstacle.m_translationLoc, obstacle.m_translation);

    abcg::glDrawArrays(GL_TRIANGLES, 0, 3);

    abcg::glBindVertexArray(0);
  }

  abcg::glUseProgram(0);
}

void Obstacles::update(float deltaTime) {

  // moving obstacles
  for (auto &obstacle : m_obstacles) {

    obstacle.m_translation -= (5.5) / 3 * deltaTime;

    // verificar se o obstaculo saiu da tela
    if (obstacle.m_translation < -5.5f) {
      obstacle.remove = true;
      obstacle.destroy();
    }
  }

  m_obstacles.remove_if([](auto &obstacle) { return obstacle.remove; });
}

void Obstacles::destroy() {
  for (auto &obstacle : m_obstacles) {
    obstacle.remove = true;
    obstacle.destroy();
  }
}

Obstacles::Obstacle Obstacles::makeObstacle() {
  Obstacle obstacle;

  std::array positions{
      glm::vec2{obstacle.position.x - obstacle.m_base / 2.0,
                obstacle.position.y - obstacle.m_height / 2.0}, // 1
      glm::vec2{obstacle.position.x + obstacle.m_base / 2.0,
                obstacle.position.y - obstacle.m_height / 2.0}, // 2
      glm::vec2{obstacle.position.x,
                obstacle.position.y + obstacle.m_height / 2.0}, // 3

  };

  // VBO
  abcg::glGenBuffers(1, &obstacle.m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, obstacle.m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Atributos
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // VAO
  abcg::glGenVertexArrays(1, &obstacle.m_VAO);

  abcg::glBindVertexArray(obstacle.m_VAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, obstacle.m_VBO);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindVertexArray(0);

  return obstacle;
}
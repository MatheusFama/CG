#include "square.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Square::create(GLuint program) {
  destroy();

  m_program = program;
  m_translation = 0.0f;
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  std::array positions{
      glm::vec2{position.x - size / 2.0, position.y - size / 2.0}, // 1
      glm::vec2{position.x + size / 2.0, position.y - size / 2.0}, // 2
      glm::vec2{position.x + size / 2.0, position.y + size / 2.0}, // 3

      glm::vec2{position.x - size / 2.0, position.y - size / 2.0}, // 1
      glm::vec2{position.x + size / 2.0, position.y + size / 2.0}, // 3
      glm::vec2{position.x - size / 2.0, position.y + size / 2.0}, // 4

  };

  // VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Atributos do programa
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

  // VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindVertexArray(0);
}

void Square::paint(const GameData &gameData) {
  if (gameData.m_state != State::Playing)
    return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  abcg::glUniform1f(m_translationLoc, m_translation);

  abcg::glDrawArrays(GL_TRIANGLES, 0, 6);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Square::update(GameData const &gameData) {

  if (gameData.m_input == Input::Up)
    m_translation += translationSpace;

  if (gameData.m_input == Input::Down) {
    m_translation -= translationSpace;
  }

  if (gameData.m_input == Input::Idle) {
    m_translation = 0.0f;
  }
}

void Square::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

glm::vec2 Square::getCenter() {
  return glm::vec2{position.x, position.y + m_translation};
}
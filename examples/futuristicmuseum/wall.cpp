#include "wall.hpp"

void Wall::create(GLuint program) {
  m_program = program;
  std::array<glm::vec3, 4> vertices{{{0.0f, -0.5f, +0.5f},
                                     {0.0f, -0.5f, -0.5f},
                                     {0.0f, +0.5f, +0.5f},
                                     {0.0f, +0.5f, -0.5f}}};

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create VAO and bind vertex attributes
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  // Save location of uniform variables
  m_modelMatrixLoc = abcg::glGetUniformLocation(program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(program, "color");
}

void Wall::paint() {
  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);
  auto const N{5};

  // parede traseira
  for (auto const x : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, y, 5.0f));
      // rotacionando modelo pois o modelo original está no espaço yz
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede frontal
  for (auto const x : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, y, -5.0f));
      // rotacionando modelo pois o modelo original está no espaço yz
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede direita
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(5.0f, y, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede esquerda
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(-5.0f, y, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  abcg::glBindVertexArray(0);
  abcg::glUseProgram(0);
}

void Wall::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
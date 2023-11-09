#include "wall.hpp"

void Wall::create(GLuint program, bool isFrontal) {

  frontal = isFrontal;
  std::array<glm::vec3, 4> verticesLateral{{{0.0f, -0.5f, +0.5f},
                                            {0.0f, -0.5f, -0.5f},
                                            {0.0f, +0.5f, +0.5f},
                                            {0.0f, +0.5f, -0.5f}}};

  std::array<glm::vec3, 4> verticesFrontal{{{-0.5f, +0.5f, 0.0f},
                                            {-0.5f, -0.5f, 0.0f},
                                            {+0.5f, +0.5f, 0.0f},
                                            {+0.5f, -0.5f, 0.0f}}};

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  if (frontal) {
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFrontal),
                       verticesFrontal.data(), GL_STATIC_DRAW);
  } else {

    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLateral),
                       verticesLateral.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

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
  abcg::glBindVertexArray(m_VAO);
  auto const N{5};

  if (frontal) {
    // parede esquerda
    for (auto const x : iter::range(-N, N + 1)) {
      for (auto const y : iter::range(-N, N + 1)) {
        // Set model matrix as a translation matrix
        glm::mat4 model{1.0f};
        model = glm::translate(model, glm::vec3(x, y, -5.0f));

        abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

        abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

        abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      }
    }

    // parede esquerda
    for (auto const x : iter::range(-N, N + 1)) {
      for (auto const y : iter::range(-N, N + 1)) {
        // Set model matrix as a translation matrix
        glm::mat4 model{1.0f};
        model = glm::translate(model, glm::vec3(x, y, 5.0f));

        abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

        abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

        abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      }
    }

  } else {

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
  }

  abcg::glBindVertexArray(0);
}

void Wall::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
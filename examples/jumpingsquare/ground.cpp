#include "ground.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Ground::create(GLuint program) {
  destroy();

  m_program = program;

  // clang-format off
  std::array positions{
    position1,
    position2
  };


  //VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);


  //Atributos no programa
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

  //VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindVertexArray(0);
}


void Ground::paint() {
  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);
 
  abcg::glDrawArrays(GL_LINE_STRIP, 0, 2);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}


void Ground::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
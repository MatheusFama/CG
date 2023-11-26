
#include "collection.hpp"

void Collection::create(GLuint program, GLuint base_program,
                        std::vector<ObjectConfiguration> configs,
                        std::string_view basePath) {

  m_program = program;
  b_program = base_program;
  objBasePath = basePath;

  for (auto &conf : configs) {
    Estatue estatue;
    Base base;

    estatue.create(m_program, conf);
    base.create(base_program, objBasePath, conf.startPosition);

    m_estatues.push_back(estatue);
    m_bases.push_back(base);
  }

  // Localizacao das variaveis uniformes
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");

  b_viewMatrixLocation = abcg::glGetUniformLocation(b_program, "viewMatrix");
  b_projMatrixLocation = abcg::glGetUniformLocation(b_program, "projMatrix");
}

void Collection::paint(glm::mat4 m_viewMatrix, glm::mat4 viewMatrix,
                       glm::mat4 projMatrix) {

  abcg::glUseProgram(m_program);

  // Configurando as matrizes de projeçao e visao
  abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,
                           &viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
                           &projMatrix[0][0]);

  for (auto &estatue : m_estatues) {
    estatue.paint(m_viewMatrix);
  }

  abcg::glUseProgram(0);

  abcg::glUseProgram(b_program);

  // Configurando as matrizes de projeçao e visao
  abcg::glUniformMatrix4fv(b_viewMatrixLocation, 1, GL_FALSE,
                           &viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(b_projMatrixLocation, 1, GL_FALSE,
                           &projMatrix[0][0]);

  for (auto &base : m_bases) {
    base.paint();
  }
  abcg::glUseProgram(0);
}

void Collection::destroy() {
  for (auto &estatue : m_estatues) {
    estatue.destroy();
  }

  for (auto &base : m_bases) {
    base.destroy();
  }
}

void Collection::update(float deltaTime) {

  for (auto &estatue : m_estatues) {
    estatue.update(deltaTime);
  }
}
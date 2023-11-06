#ifndef BASE_HPP_
#define BASE_HPP_

#include "common.hpp"
class Base {
public:
  void create(GLuint program, std::string_view path, glm::vec2 position);
  void paint();
  void destroy();

private:
  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_colorLocation{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  glm::vec2 startPosition;
  float high{0.15f};

  void loadModelFromFile(std::string_view path);
};
#endif
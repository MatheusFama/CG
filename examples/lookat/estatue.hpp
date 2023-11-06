#ifndef ESTATUE_HPP_
#define ESTATUE_HPP_

#include "common.hpp"

class Estatue {
public:
  void create(GLuint program, ObjectConfiguration &configuration);
  void paint();
  void update(float deltaTime);
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

  ObjectConfiguration config;
  bool up{true};
  float high{0.0f};
  float radius{0.0f};
  void loadModelFromFile(std::string_view path);
};
#endif
#ifndef BASE_HPP_
#define BASE_HPP_

#include "common.hpp"
class Base {
public:
  void create(GLuint program, std::string_view path, glm::vec2 position);
  void paint(glm::mat4 viewMatrix);
  void destroy();
  void loadObj(std::string_view path);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);

  [[nodiscard]] int getNumTriangles() const {
    return gsl::narrow<int>(m_indices.size()) / 3;
  }

  [[nodiscard]] glm::vec4 getKa() const { return m_Ka; }
  [[nodiscard]] glm::vec4 getKd() const { return m_Kd; }
  [[nodiscard]] glm::vec4 getKs() const { return m_Ks; }
  [[nodiscard]] float getShininess() const { return m_shininess; }

private:
  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_normalMatrixLoc{};
  GLint m_lightDirWorldSpace{};

  GLint m_IaLoc{};
  GLint m_IdLoc{};
  GLint m_IsLoc{};
  GLint m_KaLoc{};
  GLint m_KdLoc{};
  GLint m_KsLoc{};
  GLint m_shininessLoc{};

  GLint m_colorLocation{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  glm::vec2 startPosition;
  bool m_hasNormals{false};

  float high{0.15f};

  // Light and material properties
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka{0.1f, 0.1f, 0.1f, 1.0f};
  glm::vec4 m_Kd{0.7f, 0.7f, 0.7f, 1.0f};
  glm::vec4 m_Ks{1.0f};
  float m_shininess{25.0f};

  // void loadModelFromFile(std::string_view path);
  void computeNormals();
  void createBuffers();
  void standardize();
};
#endif
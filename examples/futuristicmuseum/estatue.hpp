#ifndef ESTATUE_HPP_
#define ESTATUE_HPP_

#include "common.hpp"

class Estatue {
public:
  void create(GLuint program, ObjectConfiguration configuration);
  void paint(glm::mat4 m_viewMatrix);
  void update(float deltaTime);
  void destroy();

  [[nodiscard]] glm::vec4 getKa() const { return m_Ka; }
  [[nodiscard]] glm::vec4 getKd() const { return m_Kd; }
  [[nodiscard]] glm::vec4 getKs() const { return m_Ks; }
  [[nodiscard]] float getShininess() const { return m_shininess; }
  [[nodiscard]] bool isUVMapped() const { return m_hasTexCoords; }

private:
  void loadDiffuseTexture(std::string_view path);
  void loadNormalTexture(std::string_view path);
  void loadObj(std::string_view path);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);

  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_modelNormalMatrixLoc{};
  // GLint m_colorLocation{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  bool up{true};
  float high{0.0f};
  float radius{0.0f};

  glm::vec2 startPosition{0, 0};
  // glm::vec3 color{0, 0, 0};
  float minHigh{0.0f};
  float maxHigh{0.0f};
  bool verticalRotate{false};
  float radiusVerticalRotate{0.0f};
  float scale{0.0f};
  std::string path{""};
  bool choosed{false};
  float rotationSpeed{0.0f};
  // float triangulesToDraw{1.0f};
  std::string normalTexturepath{""};
  std::string difuseTexturepath{""};

  // Light and material properties
  glm::vec4 m_lightDir{0.5f, -1.0f, 0.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};

  glm::vec4 m_Ka{};
  glm::vec4 m_Kd{};
  glm::vec4 m_Ks{};

  float m_shininess{};
  bool m_hasNormals{false};
  bool m_hasTexCoords{false};
  GLuint m_diffuseTexture{};
  GLuint m_normalTexture{};
  int m_mappingMode{3};

  void computeNormals();
  void computeTangents();
  void createBuffers();
};
#endif
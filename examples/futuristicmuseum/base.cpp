#include "base.hpp"
#include <unordered_map>

// Explicit specialization of std::hash for Vertex
template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{std::hash<glm::vec3>()(vertex.position)};
    auto const h2{std::hash<glm::vec3>()(vertex.normal)};
    return abcg::hashCombine(h1, h2);
  }
};

void Base::computeNormals() {
  // Clear previous vertex normals
  for (auto &vertex : m_vertices) {
    vertex.normal = glm::vec3(0.0f);
  }

  // Compute face normals
  for (auto const offset : iter::range(0UL, m_indices.size(), 3UL)) {
    // Get face vertices
    auto &a{m_vertices.at(m_indices.at(offset + 0))};
    auto &b{m_vertices.at(m_indices.at(offset + 1))};
    auto &c{m_vertices.at(m_indices.at(offset + 2))};

    // Compute normal
    auto const edge1{b.position - a.position};
    auto const edge2{c.position - b.position};
    auto const normal{glm::cross(edge1, edge2)};

    // Accumulate on vertices
    a.normal += normal;
    b.normal += normal;
    c.normal += normal;
  }

  // Normalize
  for (auto &vertex : m_vertices) {
    vertex.normal = glm::normalize(vertex.normal);
  }

  m_hasNormals = true;
}

void Base::createBuffers() {
  // Delete previous buffers
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);

  // VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER,
                     sizeof(m_vertices.at(0)) * m_vertices.size(),
                     m_vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(m_indices.at(0)) * m_indices.size(),
                     m_indices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Base::loadObj(std::string_view path) {
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(path.data())) {
    if (!reader.Error().empty()) {
      throw abcg::RuntimeError(
          fmt::format("Failed to load model {} ({})", path, reader.Error()));
    }
    throw abcg::RuntimeError(fmt::format("Failed to load model {}", path));
  }

  if (!reader.Warning().empty()) {
    fmt::print("Warning: {}\n", reader.Warning());
  }

  auto const &attrib{reader.GetAttrib()};
  auto const &shapes{reader.GetShapes()};

  m_vertices.clear();
  m_indices.clear();

  m_hasNormals = false;

  // A key:value map with key=Vertex and value=index
  std::unordered_map<Vertex, GLuint> hash{};

  // Loop over shapes
  for (auto const &shape : shapes) {
    // Loop over indices
    for (auto const offset : iter::range(shape.mesh.indices.size())) {
      // Access to vertex
      auto const index{shape.mesh.indices.at(offset)};

      // Vertex position
      auto const startIndex{3 * index.vertex_index};
      glm::vec3 position{attrib.vertices.at(startIndex + 0),
                         attrib.vertices.at(startIndex + 1),
                         attrib.vertices.at(startIndex + 2)};

      // Vertex normal
      glm::vec3 normal{};
      if (index.normal_index >= 0) {
        m_hasNormals = true;
        auto const normalStartIndex{3 * index.normal_index};
        normal = {attrib.normals.at(normalStartIndex + 0),
                  attrib.normals.at(normalStartIndex + 1),
                  attrib.normals.at(normalStartIndex + 2)};
      }

      Vertex const vertex{.position = position, .normal = normal};

      // If hash doesn't contain this vertex
      if (!hash.contains(vertex)) {
        // Add this index (size of m_vertices)
        hash[vertex] = m_vertices.size();
        // Add this vertex
        m_vertices.push_back(vertex);
      }

      m_indices.push_back(hash[vertex]);
    }
  }

  if (!m_hasNormals) {
    computeNormals();
  }

  createBuffers();
}

void Base::render(int numTriangles) const {
  abcg::glBindVertexArray(m_VAO);

  auto const numIndices{(numTriangles < 0) ? m_indices.size()
                                           : numTriangles * 3};

  abcg::glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);
}

void Base::setupVAO(GLuint program) {
  // Release previous VAO
  abcg::glDeleteVertexArrays(1, &m_VAO);

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);

  // Bind EBO and VBO
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  // Bind vertex attributes
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  if (positionAttribute >= 0) {
    abcg::glEnableVertexAttribArray(positionAttribute);
    abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vertex), nullptr);
  }

  auto const normalAttribute{abcg::glGetAttribLocation(program, "inNormal")};
  if (normalAttribute >= 0) {
    abcg::glEnableVertexAttribArray(normalAttribute);
    auto const offset{offsetof(Vertex, normal)};
    abcg::glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vertex),
                                reinterpret_cast<void *>(offset));
  }

  // End of binding
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);
}

// void Base::loadModelFromFile(std::string_view path) {
//   tinyobj::ObjReader reader;

//   if (!reader.ParseFromFile(path.data())) {
//     if (!reader.Error().empty()) {
//       throw abcg::RuntimeError(
//           fmt::format("Failed to load model {} ({})", path, reader.Error()));
//     }
//     throw abcg::RuntimeError(fmt::format("Failed to load model {}", path));
//   }

//   if (!reader.Warning().empty()) {
//     fmt::print("Warning: {}\n", reader.Warning());
//   }

//   auto const &attributes{reader.GetAttrib()};
//   auto const &shapes{reader.GetShapes()};

//   m_vertices.clear();
//   m_indices.clear();

//   // A key:value map with key=Vertex and value=index
//   std::unordered_map<Vertex, GLuint> hash{};

//   // Loop over shapes
//   for (auto const &shape : shapes) {
//     // Loop over indices
//     for (auto const offset : iter::range(shape.mesh.indices.size())) {
//       // Access to vertex
//       auto const index{shape.mesh.indices.at(offset)};

//       // Vertex position
//       auto const startIndex{3 * index.vertex_index};
//       auto const vx{attributes.vertices.at(startIndex + 0)};
//       auto const vy{attributes.vertices.at(startIndex + 1)};
//       auto const vz{attributes.vertices.at(startIndex + 2)};

//       Vertex const vertex{.position = {vx, vy, vz}};

//       // If map doesn't contain this vertex
//       if (!hash.contains(vertex)) {
//         // Add this index (size of m_vertices)
//         hash[vertex] = m_vertices.size();
//         // Add this vertex
//         m_vertices.push_back(vertex);
//       }

//       m_indices.push_back(hash[vertex]);
//     }
//   }
// }

void Base::create(GLuint program, std::string_view path, glm::vec2 position) {
  startPosition = position;
  m_program = program;

  // Get location of uniform variables
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  // m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLocation = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_normalMatrixLoc = abcg::glGetUniformLocation(m_program, "normalMatrix");
  m_lightDirWorldSpace =
      abcg::glGetUniformLocation(m_program, "lightDirWorldSpace");

  m_shininessLoc = abcg::glGetUniformLocation(m_program, "shininess");
  m_IaLoc = abcg::glGetUniformLocation(m_program, "Ia");
  m_IdLoc = abcg::glGetUniformLocation(m_program, "Id");
  m_IsLoc = abcg::glGetUniformLocation(m_program, "Is");
  m_KaLoc = abcg::glGetUniformLocation(m_program, "Ka");
  m_KdLoc = abcg::glGetUniformLocation(m_program, "Kd");
  m_KsLoc = abcg::glGetUniformLocation(m_program, "Ks");

  // m_colorLocation = abcg::glGetUniformLocation(m_program, "color");

  // Load model
  // loadModelFromFile(path);
  loadObj(path);
  setupVAO(m_program);
}

void Base::paint(glm::mat4 viewMatrix) {
  abcg::glBindVertexArray(m_VAO);

  glm::mat4 model{1.0f};
  model =
      glm::translate(model, glm::vec3(startPosition.x, high, startPosition.y));
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
  model = glm::scale(model, glm::vec3(0.1f));

  // abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
  // &m_projMatrix[0][0]);

  abcg::glUniform4fv(m_lightDirWorldSpace, 1, &m_lightDir.x);
  abcg::glUniform4fv(m_IaLoc, 1, &m_Ia.x);
  abcg::glUniform4fv(m_IdLoc, 1, &m_Id.x);
  abcg::glUniform4fv(m_IsLoc, 1, &m_Is.x);

  // Set uniform variables for the current model
  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4fv(m_KaLoc, 1, &m_Ka.x);
  abcg::glUniform4fv(m_KdLoc, 1, &m_Kd.x);
  abcg::glUniform4fv(m_KsLoc, 1, &m_Ks.x);
  abcg::glUniform1f(m_shininessLoc, m_shininess);

  auto const modelViewMatrix{glm::mat3(viewMatrix * model)};
  auto const normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(m_normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);
  render(-1);

  // abcg::glUniform4f(m_colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
  //  abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT,
  //                       nullptr);

  abcg::glBindVertexArray(0);
}

void Base::destroy() {
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
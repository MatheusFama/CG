#include "estatue.hpp"
#include <unordered_map>

// Explicit specialization of std::hash for Vertex
template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{std::hash<glm::vec3>()(vertex.position)};
    return h1;
  }
};

void Estatue::loadModelFromFile(std::string_view path) {
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

  auto const &attributes{reader.GetAttrib()};
  auto const &shapes{reader.GetShapes()};

  m_vertices.clear();
  m_indices.clear();

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
      auto const vx{attributes.vertices.at(startIndex + 0)};
      auto const vy{attributes.vertices.at(startIndex + 1)};
      auto const vz{attributes.vertices.at(startIndex + 2)};

      Vertex const vertex{.position = {vx, vy, vz}};

      // If map doesn't contain this vertex
      if (!hash.contains(vertex)) {
        // Add this index (size of m_vertices)
        hash[vertex] = m_vertices.size();
        // Add this vertex
        m_vertices.push_back(vertex);
      }

      m_indices.push_back(hash[vertex]);
    }
  }
}

void Estatue::create(GLuint program, ObjectConfiguration &configuration) {
  m_program = program;

  config.startPosition = configuration.startPosition;
  config.color = configuration.color;
  config.minHigh = configuration.minHigh;
  config.maxHigh = configuration.maxHigh;
  config.verticalRotate = configuration.verticalRotate;
  config.radiusVerticalRotate = configuration.radiusVerticalRotate;
  config.scale = configuration.scale;
  config.path = configuration.path;
  config.choosed = configuration.choosed;

  fmt::print("CONFI\nx: {:.2f} , y: {:.2f} \n", config.startPosition.x,
             config.startPosition.y);

  fmt::print("CONFIGURATION\nx: {:.2f} , y: {:.2f} \n",
             configuration.startPosition.x, configuration.startPosition.y);
  high = config.minHigh;
  // Get location of uniform variables
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLocation = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_colorLocation = abcg::glGetUniformLocation(m_program, "color");

  // Load model
  loadModelFromFile(config.path);

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER,
                     sizeof(m_vertices.at(0)) * m_vertices.size(),
                     m_vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(m_indices.at(0)) * m_indices.size(),
                     m_indices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Estatue::update(float deltaTime) {
  radius += 0.5 * deltaTime;

  if (radius >= 360)
    radius -= 360;

  if (up)
    high += 0.1 * deltaTime;
  else
    high -= 0.1 * deltaTime;

  if (high >= config.maxHigh)
    up = false;
  if (high <= config.minHigh)
    up = true;
}
void Estatue::paint() {

  abcg::glBindVertexArray(m_VAO);

  // fmt::print("x: {:.2f} (min), y: {:.2f} \n", config.startPosition.x,
  //            config.startPosition.y);

  // fmt::print("PAINT\nx: {:.2f} , y: {:.2f} \n", config.startPosition.x,
  //            config.startPosition.y);

  //  Draw white bunny
  glm::mat4 model{1.0f};
  model = glm::translate(
      model, glm::vec3(config.startPosition.x, high, config.startPosition.y));
  model = glm::rotate(model, radius, glm::vec3(0, 1, 0));

  if (config.verticalRotate)
    model = glm::rotate(model, config.radiusVerticalRotate, glm::vec3(1, 0, 0));

  model = glm::scale(model, glm::vec3(config.scale));

  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(m_colorLocation, config.color.x, config.color.y,
                    config.color.z, 1.0f);
  abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT,
                       nullptr);

  abcg::glBindVertexArray(0);
}

void Estatue::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
  abcg::glDeleteBuffers(1, &m_EBO);
}
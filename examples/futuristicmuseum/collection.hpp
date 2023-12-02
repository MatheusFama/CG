#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include "abcgOpenGL.hpp"

#include "base.hpp"
#include "common.hpp"
#include "estatue.hpp"

class Collection {
public:
  void create(GLuint program, GLuint base_program,
              std::vector<ObjectConfiguration> configs,
              std::string_view basePath);
  void paint(glm::mat4 m_viewMatrix, glm::mat4 projMatrix);
  void update(float deltaTime);
  void destroy();

private:
  GLuint m_program{};
  GLuint b_program{};
  GLuint m_viewMatrixLocation{};
  GLuint m_projMatrixLocation{};
  GLuint b_viewMatrixLocation{};
  GLuint b_projMatrixLocation{};

  std::vector<Base> m_bases;
  std::vector<Estatue> m_estatues;
  std::string_view objBasePath;
};

#endif
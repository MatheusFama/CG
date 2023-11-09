#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include "abcgOpenGL.hpp"

#include "base.hpp"
#include "common.hpp"
#include "estatue.hpp"

class Collection {
public:
  void create(GLuint program, std::vector<ObjectConfiguration> configs,
              std::string_view basePath);
  void paint();
  void update(float deltaTime);
  void destroy();

private:
  GLuint m_program{};
  std::vector<Base> m_bases;
  std::vector<Estatue> m_estatues;
  std::string_view objBasePath;
};

#endif
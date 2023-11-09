
#include "collection.hpp"

void Collection::create(GLuint program,
                        std::vector<ObjectConfiguration> configs,
                        std::string_view basePath) {

  m_program = program;
  objBasePath = basePath;

  for (auto &conf : configs) {
    Estatue estatue;
    Base base;

    estatue.create(m_program, conf);
    base.create(m_program, objBasePath, conf.startPosition);

    m_estatues.push_back(estatue);
    m_bases.push_back(base);
  }
}

void Collection::paint() {

  for (auto &estatue : m_estatues) {
    estatue.paint();
  }

  for (auto &base : m_bases) {
    base.paint();
  }
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
#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

#include "ground.hpp"
#include "obstacles.hpp"
#include "square.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;
  void checkCollisions();

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_objectsProgram{};
  GLuint m_obstaclesProgram{};
  GLuint m_groundProgram{};

  GameData m_gameData;

  Ground m_ground;

  Square m_square;

  Obstacles m_obstacles;

  abcg::Timer m_restartWaitTimer;
  abcg::Timer m_restartGameWaitTimer;

  float randomTime{0.0};

  ImFont *m_font{};

  std::default_random_engine m_randomEngine;

  std::uniform_real_distribution<float> m_randomDist{1.0f, 5.0f};

  void restart();
};

#endif
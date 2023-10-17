#include "window.hpp"
#include "fmt/format.h"
#include "iostream"
#include "string"
void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Carregando fonte
  auto const filename{assetsPath + "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 60.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError("Cannot load font file");
  }

  // Programas para redenrizar objetos
  m_objectsProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "objects.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "objects.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_obstaclesProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "obstacle.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "obstacle.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_groundProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "ground.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "ground.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  // Gerador de numeros aleatórios
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  randomTime = m_randomDist(m_randomEngine);

  restart();
}

void Window::restart() {
  m_restartGameWaitTimer.restart();
  m_gameData.m_state = State::Playing;

  m_square.create(m_objectsProgram);
  m_obstacles.create(m_obstaclesProgram);
  m_ground.create(m_groundProgram);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Esperar 5s para reiniciar a partida
  if (m_gameData.m_state != State::Playing &&
      m_restartGameWaitTimer.elapsed() > 5) {
    restart();
    return;
  }

  if (m_square.m_translation >= m_gameData.maxHigh)
    m_gameData.m_input = Input::Down;

  if (m_square.m_translation < m_gameData.minHigh) {
    m_gameData.m_input = Input::Idle;
  }

  if (m_restartWaitTimer.elapsed() >= randomTime) {
    randomTime = m_randomDist(m_randomEngine);

    m_restartWaitTimer.restart();
    m_obstacles.m_obstacles.push_back(m_obstacles.makeObstacle());
  }

  m_obstacles.update(deltaTime);
  m_square.update(m_gameData, deltaTime);

  if (m_gameData.m_state == State::Playing) {
    checkCollisions();
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  m_square.paint(m_gameData);
  m_obstacles.paint(m_gameData);
  m_ground.paint();
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    auto const size{ImVec2(300, 125)};
    auto const position{ImVec2((m_viewportSize.x - size.x) / 2.0f,
                               (m_viewportSize.y - size.y) / 2.0f)};

    auto const sizePlaying{ImVec2(300, 85)};
    auto const positionPlaying{
        ImVec2((m_viewportSize.x - size.x), (m_viewportSize.y - size.y))};
    ImGui::GetIO().FontGlobalScale = 0.5f;

    if (m_gameData.m_state == State::Playing) {
      ImGui::SetNextWindowPos(positionPlaying);
      ImGui::SetNextWindowSize(sizePlaying);
    } else {
      ImGui::SetNextWindowPos(position);
      ImGui::SetNextWindowSize(size);
    }

    ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);

    if (m_gameData.m_state == State::GameOver) {
      const auto gameOverStr = fmt::format("Temp: {} s", m_gameData.scoreTime);
      ImGui::TextWrapped("Game Over!");
      ImGui::TextWrapped(gameOverStr.c_str());

    } else {
      const auto timeStr =
          fmt::format("Tempo: {}", m_restartGameWaitTimer.elapsed());
      ImGui::Text(timeStr.c_str());
    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void Window::onEvent(SDL_Event const &event) {
  // Enquanto square estiver no ar, não será possivel interagir
  if (m_gameData.m_input == Input::Up || m_gameData.m_input == Input::Down)
    return;
  // Eventos de teclado
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    m_gameData.m_input = Input::Up;
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_objectsProgram);
  abcg::glDeleteProgram(m_obstaclesProgram);
  abcg::glDeleteProgram(m_groundProgram);

  m_square.destroy();
  m_obstacles.destroy();
  m_ground.destroy();
}

void Window::checkCollisions() {

  glm::vec2 sqrCenter, obsCenter;

  sqrCenter = m_square.getCenter();

  for (auto &obstacle : m_obstacles.m_obstacles) {

    obsCenter = obstacle.getCenter();

    bool collisionX =
        sqrCenter.x + m_square.size >= obsCenter.x &&
        obsCenter.x + obstacle.m_base / (10 * obstacle.m_base) >= sqrCenter.x;

    bool collisionY =
        sqrCenter.y + m_square.size >= obsCenter.y &&
        obsCenter.y + obstacle.m_height / (10 * obstacle.m_height) >=
            sqrCenter.y;

    // Caso haja colisão a partida será finalizada
    if (collisionX && collisionY) {
      m_gameData.m_state = State::GameOver;
      m_gameData.scoreTime = m_restartGameWaitTimer.elapsed();
      m_restartGameWaitTimer.restart();
    }
  }
}
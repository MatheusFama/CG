#include "window.hpp"

void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_q)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_truckSpeed = 1.0f;
  }
  if (event.type == SDL_KEYUP) {
    if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) &&
        m_dollySpeed > 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) &&
        m_dollySpeed < 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) &&
        m_panSpeed < 0)
      m_panSpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_RIGHT ||
         event.key.keysym.sym == SDLK_d) &&
        m_panSpeed > 0)
      m_panSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_q && m_truckSpeed < 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_e && m_truckSpeed > 0)
      m_truckSpeed = 0.0f;
  }
}

void Window::onCreate() {
  auto const &assetsPath{abcg::Application::getAssetsPath()};

  // Gerador de cores aleatórias
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_real_distribution randomColor{0.0f, 1.0f};

  // Gerando lista de posições
  positions.clear();

  positions.push_back(glm::vec2(-1.0f, 0.0f));
  positions.push_back(glm::vec2(-1.0f, -1.0f));
  positions.push_back(glm::vec2(-1.0f, -2.0f));
  positions.push_back(glm::vec2(-1.0f, -3.0f));
  positions.push_back(glm::vec2(1.0f, 0.0f));
  positions.push_back(glm::vec2(1.0f, -1.0f));
  positions.push_back(glm::vec2(1.0f, -2.0f));
  positions.push_back(glm::vec2(1.0f, -3.0f));

  // Lista com todas as configurações dos modelos
  allConfigs.clear();

  auto const bunnyPath = assetsPath + "bunny.obj";
  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.15f, 0.45f, false, 0.0f, 0.1f, bunnyPath, false});

  auto const catPath = assetsPath + "cat.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.005f, catPath, false});

  auto const alienPath = assetsPath + "alien_dog.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.16f, 0.45f, false, -90.0f, 0.01f, alienPath, false});

  auto const spider_monkeyPath = assetsPath + "spider_monkey.obj";
  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.0025f, spider_monkeyPath, false});

  auto const humanPath = assetsPath + "humanbody.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, false, -90.0f, 0.08f, humanPath, false});

  auto const eyePath = assetsPath + "eyeball.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.45f, false, -90.0f, 0.05f, eyePath, false});

  auto const treePath = assetsPath + "tree.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.45f, false, -90.0f, 0.03f, treePath, false});

  auto const wolfPath = assetsPath + "wolf_one.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.15f, 0.45f, false, -90.0f, 0.55f, wolfPath, false});

  auto const skullPath = assetsPath + "skull.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.01f, skullPath, false});

  auto const handPath = assetsPath + "hand.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.01f, handPath, false});

  auto const stonePath = assetsPath + "stone.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, false, -90.0f, 0.055f, stonePath, false});

  std::uniform_int_distribution randomPosition{0, 10};
  for (auto &pos : positions) {

    bool check = true;
    do {
      int i = randomPosition(m_randomEngine);
      auto &config = allConfigs[i];
      if (!config.choosed) {
        config.startPosition = pos;
        config.choosed = true;
        check = false;
      }
    } while (check);
  }
  // Removendo os que nao foram escolhidos
  allConfigs.erase(
      std::remove_if(allConfigs.begin(), allConfigs.end(),
                     [](const ObjectConfiguration &o) { return !o.choosed; }),
      allConfigs.end());

  abcg::glClearColor(0, 0, 0, 1);

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "lookat.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "lookat.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

  auto const objBasePath = assetsPath + "cilindro.obj";

  // Get location of uniform variables
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");

  for (auto &conf : allConfigs) {
    Estatue estatue;
    Base base;

    estatue.create(m_program, conf);
    base.create(m_program, objBasePath, conf.startPosition);

    m_estatues.push_back(estatue);
    m_bases.push_back(base);
  }

  // auto const objPath = assetsPath + "hand.obj";
  // ObjectConfiguration config = {glm::vec2(1.0f, -1.0f),
  //                               glm::vec3(randomColor(m_randomEngine),
  //                                         randomColor(m_randomEngine),
  //                                         randomColor(m_randomEngine)),
  //                               0.2f,
  //                               0.45f,
  //                               true,
  //                               -90.0f,
  //                               0.01f,
  //                               objPath,
  //                               true};
  // auto const objPath1 = assetsPath + "cat.obj";
  // ObjectConfiguration config1 = {glm::vec2(1.0f, 0.0f),
  //                                glm::vec3(randomColor(m_randomEngine),
  //                                          randomColor(m_randomEngine),
  //                                          randomColor(m_randomEngine)),
  //                                0.2f,
  //                                0.45f,
  //                                true,
  //                                -90.0f,
  //                                0.005f,
  //                                objPath1,
  //                                false};

  // m_estatue.create(m_program, config);
  // m_base.create(m_program, objBasePath, glm::vec2(1.0f, -1.0f));

  // m_estatue1.create(m_program, config1);
  // m_base1.create(m_program, objBasePath, glm::vec2(1.0f, 0.0f));

  m_ground.create(m_program);
}

void Window::onPaint() {
  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Set uniform variables for viewMatrix and projMatrix
  // These matrices are used for every scene object
  abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,
                           &m_camera.getViewMatrix()[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
                           &m_camera.getProjMatrix()[0][0]);

  // // Draw estatue
  // m_estatue.paint();
  // m_base.paint();

  // // Draw estatue
  // m_estatue1.paint();
  // m_base1.paint();

  for (auto &estatue : m_estatues) {
    estatue.paint();
  }

  for (auto &base : m_bases) {
    base.paint();
  }

  // Draw ground
  m_ground.paint();

  abcg::glUseProgram(0);
}

void Window::onPaintUI() { abcg::OpenGLWindow::onPaintUI(); }

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;
  m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
  m_ground.destroy();

  for (auto &estatue : m_estatues) {
    estatue.destroy();
  }

  for (auto &base : m_bases) {
    base.destroy();
  }

  // m_estatue.destroy();
  // m_base.destroy();

  // m_estatue1.destroy();
  // m_base1.destroy();
  abcg::glDeleteProgram(m_program);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  for (auto &estatue : m_estatues) {
    estatue.update(deltaTime);
  }

  // m_estatue.update(deltaTime);
  // m_estatue1.update(deltaTime);
  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);
}
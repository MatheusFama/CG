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
  std::uniform_real_distribution randomSpeed{0.2f, 0.5f};

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

  // positions.push_back(glm::vec2(-2.5f, 0.0f));
  // positions.push_back(glm::vec2(-2.5f, -1.0f));
  // positions.push_back(glm::vec2(-2.5f, -2.0f));
  // positions.push_back(glm::vec2(-2.5f, -3.0f));
  // positions.push_back(glm::vec2(2.5f, 0.0f));
  // positions.push_back(glm::vec2(2.5f, -1.0f));
  // positions.push_back(glm::vec2(2.5f, -2.0f));
  // positions.push_back(glm::vec2(2.5f, -3.0f));

  // Lista com todas as configurações dos modelos
  allConfigs.clear();

  auto const catPath = assetsPath + "cat.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.005f, catPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const bunnyPath = assetsPath + "bunny.obj";
  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.15f, 0.45f, false, 0.0f, 0.1f, bunnyPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const dogPath = assetsPath + "dog.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.005f, dogPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const dolphinPath = assetsPath + "dolphin.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.0035f, dolphinPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const whalePath = assetsPath + "whale.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.55f, true, -90.0f, 0.001f, whalePath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const pufferFishPath = assetsPath + "puffer_fish.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.55f, true, -90.0f, 0.01f, pufferFishPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const dragonPath = assetsPath + "dragon.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.55f, false, -90.0f, 0.001f, dragonPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const birdPath = assetsPath + "bird.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.01f, birdPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const alienPath = assetsPath + "alien_dog.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.16f, 0.45f, false, -90.0f, 0.01f, alienPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const spider_monkeyPath = assetsPath + "spider_monkey.obj";
  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.0025f, spider_monkeyPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const humanPath = assetsPath + "humanbody.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, false, -90.0f, 0.08f, humanPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const eyePath = assetsPath + "eyeball.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.45f, false, -90.0f, 0.05f, eyePath, false,
       randomSpeed(m_randomEngine), 0.85});

  auto const treePath = assetsPath + "tree.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.3f, 0.45f, false, -90.0f, 0.03f, treePath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const wolfPath = assetsPath + "wolf_one.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.15f, 0.45f, false, -90.0f, 0.55f, wolfPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const skullPath = assetsPath + "skull.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.01f, skullPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const handPath = assetsPath + "hand.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.01f, handPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const stonePath = assetsPath + "stone.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, false, -90.0f, 0.055f, stonePath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const trex = assetsPath + "t_rex.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, false, -90.0f, 0.0005f, trex, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const horsePath = assetsPath + "horse.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.0025f, horsePath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto si = (int)allConfigs.size() - 1;
  std::uniform_int_distribution randomPosition{0, si};
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

  abcg::glEnable(GL_DEPTH_TEST);

  // Criando program
  m_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "phong.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "phong.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  base_program = abcg::createOpenGLProgram(
      {{.source = assetsPath + "futuristicmuseum.vert",
        .stage = abcg::ShaderStage::Vertex},
       {.source = assetsPath + "futuristicmuseum.frag",
        .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

  // Localizacao das variaveis uniformes
  // m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  // m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");

  auto const objBasePath = assetsPath + "cilindro.obj";
  m_collection.create(m_program, base_program, allConfigs, objBasePath);

  m_ground.create(base_program);
  m_wall.create(base_program);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  // abcg::glUseProgram(m_program);

  // Configurando as matrizes de projeçao e visao
  // abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,
  //                          &m_camera.getViewMatrix()[0][0]);
  // abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
  //                          &m_camera.getProjMatrix()[0][0]);

  // Desenhando a coleçao de obras
  m_collection.paint(m_camera.getViewMatrix(), m_camera.getViewMatrix(),
                     m_camera.getProjMatrix());

  // Desenhando o chao
  m_ground.paint();
  m_wall.paint();

  // abcg::glUseProgram(0);
}

void Window::onPaintUI() { abcg::OpenGLWindow::onPaintUI(); }

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;
  m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {

  // m_ground.destroy();
  // m_wall.destroy();

  m_collection.destroy();

  abcg::glDeleteProgram(m_program);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Atualizando coleção
  m_collection.update(deltaTime);

  // Atualizando camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);
}
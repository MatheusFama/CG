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

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f,
                        0.0005f, assetsPath + "/horse/10026_Horse_v01-it2.obj",
                        false, randomSpeed(m_randomEngine), "",
                        assetsPath + "/horse/Horse_v01.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f,
                        0.005f, assetsPath + "/duck/12248_Bird_v1_L2.obj",
                        false, randomSpeed(m_randomEngine), "",
                        assetsPath + "/duck/12248_Bird_v1_diff.png", 3});

  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, false, -90.0f, 0.05f,
       assetsPath + "/stone/Stone.obj", false, randomSpeed(m_randomEngine),
       assetsPath + "/stone/normal.png", assetsPath + "/stone/rough.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f,
                        0.008f,
                        assetsPath + "/dog/13463_Australian_Cattle_Dog_v3.obj",
                        false, randomSpeed(m_randomEngine),
                        assetsPath + "/dog/Australian_Cattle_Dog_bump.png",
                        assetsPath + "/dog/Australian_Cattle_Dog_dif.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.3f, 0.45f, false, -90.0f, 0.3f,
                        assetsPath + "/cup/coffee_cup_obj.obj", false,
                        randomSpeed(m_randomEngine),
                        assetsPath + "/cup/normal.png",
                        assetsPath + "/cup/Base_color.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.3f, 0.45f, false, -90.0f,
                        0.05f, assetsPath + "/moon/Moon 2K.obj", false,
                        randomSpeed(m_randomEngine),
                        assetsPath + "/moon/Bump_2K.png",
                        assetsPath + "/moon/Diffuse_2K.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.25f, 0.45f, false, -90.0f,
                        0.001f, assetsPath + "/roman_lamp/roman_lamp.obj",
                        false, randomSpeed(m_randomEngine),
                        assetsPath + "/roman_lamp/roman_lamp_normal.jpg",
                        assetsPath + "/roman_lamp/roman_lamp_diffuse.jpg", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.15f, 0.45f, false, -90.0f,
                        0.55f, assetsPath + "/wolf/Wolf_One_obj.obj", false,
                        randomSpeed(m_randomEngine), "",
                        assetsPath + "/wolf/Wolf_Body.jpg", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.3f, 0.45f, false, -90.0f,
                        0.05f, assetsPath + "/eye/eyeball.obj", false,
                        randomSpeed(m_randomEngine), "",
                        assetsPath + "/eye/Eye_D.jpg", 3});

  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f), 0.2f, 0.45f, true, -90.0f, 0.0025f,
       assetsPath + "/monkey/12958_Spider_Monkey_v1_l2.obj", false,
       randomSpeed(m_randomEngine),
       assetsPath + "/monkey/Map__3_Normal Bump.jpg",
       assetsPath + "/monkey/12958_Spider_Monkey_diff.jpg", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f, 0.01f,
                        assetsPath + "/bird/12213_Bird_v1_l3.obj", false,
                        randomSpeed(m_randomEngine),
                        assetsPath + "/bird/Map__7_Normal Bump.jpg",
                        assetsPath + "/bird/12213_bird_diffuse.jpg", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.3f, 0.55f, true, -90.0f,
                        0.001f, assetsPath + "/whale/10054_Whale_v2_L3.obj",
                        false, randomSpeed(m_randomEngine), "",
                        assetsPath + "/whale/10054_Whale_Diffuse_v2.jpg", 3});

  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f, 0.0035f,
       assetsPath + "/dolphin/10014_dolphin_v2_max2011_it2.obj", false,
       randomSpeed(m_randomEngine), "",
       assetsPath + "/dolphin/10014_dolphin_v1_Diffuse.png", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f, 0.01f,
                        assetsPath + "/skull/12140_Skull_v3_L2.obj", false,
                        randomSpeed(m_randomEngine), "",
                        assetsPath + "/skull/Skull.jpg", 3});

  allConfigs.push_back({glm::vec2(0.0f, 0.0f), 0.2f, 0.45f, true, -90.0f,
                        0.005f, assetsPath + "/cat/12221_Cat_v1_l3.obj", false,
                        randomSpeed(m_randomEngine),
                        assetsPath + "/cat/Cat_bump.jpg",
                        assetsPath + "/cat/Cat_diffuse.jpg", 3});

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
      abcg::createOpenGLProgram({{.source = assetsPath + "normalmapping.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "normalmapping.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  base_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "phong.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "phong.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  groundWall_program = abcg::createOpenGLProgram(
      {{.source = assetsPath + "futuristicmuseum.vert",
        .stage = abcg::ShaderStage::Vertex},
       {.source = assetsPath + "futuristicmuseum.frag",
        .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

  auto const objBasePath = assetsPath + "cilindro.obj";
  m_collection.create(m_program, base_program, allConfigs, objBasePath);

  m_ground.create(groundWall_program);
  m_wall.create(groundWall_program);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  // Desenhando a coleçao de obras
  m_collection.paint(m_camera.getViewMatrix(), m_camera.getProjMatrix());

  // Desenhando o chao
  m_ground.paint(m_camera.getViewMatrix(), m_camera.getProjMatrix());
  m_wall.paint(m_camera.getViewMatrix(), m_camera.getProjMatrix());
}

void Window::onPaintUI() { abcg::OpenGLWindow::onPaintUI(); }

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;
  m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
  m_ground.destroy();
  m_wall.destroy();
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
# FuturisticMuseum
* Nome: Matheus Fama
* RA: 11040615
  
## Descrição
* O FuturisticMuseum proporciona uma visão inovadora ao representar um museu do futuro, onde cada obra do acervo é cuidadosamente disposta em sua própria plataforma, girando e movendo-se verticalmente, em uma simulação de gravidade artificial. Esse design permite que o observador aprecie cada peça de arte sob uma variedade de ângulos, proporcionando uma experiência única e dinâmica.
  A ideia foi inspirada observando os projetos em aula. Os modelos 3d quando sem textura pareciam estátuas e, para demonstrar os conceitos aprendidos em aula, decidi movimentar os modelos das mais diversas formas dando uma perspectiva futurista para a cena.

Você pode ver o projeto [aqui](https://matheusfama.github.io/CG.github.io/public/futuristicmuseum.html).

### Museu
<table>
  <tr>
    <td>
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/futuristcmuseum.gif" width="300">
    </td>
  </tr>
</table>


## Organização do Projeto
O projeto foi separado nas seguintes classes:

* Base: classe que representa a base onde as estátuas estarão.
* Estatue: classe que representa a obra que estará sob as bases.
* Collection: classe que controlará o acervo de obras.
* Ground : classe que representa o terreno.
* Wall: classe que representa as quatro paredes da cena.
* Camera: classe que representa a visão do observador.


### Organização dos arquivos
<pre>
<code>jumpingsquare/
│   base.cpp
│   base.hpp
│   camera.cpp
│   camera.hpp
│   collection.cpp
│   colection.hpp
│   CMakeLists.txt
│   common.hpp
|   estatue.hpp
|   estatue.cpp
|   ground.hpp
|   ground.cpp
|   wall.hpp
|   wall.cpp  
│   main.cpp
│   window.hpp
│   window.cpp
│
└───assets/
    │   futuristicmuseum.frag
    └   futuristicmuseum.vert</code></pre>

### Cenário
O cenário será formado pelos seguintes objetos:
* A plataforma formada por GL_TRIANGLES;
* A estátua formada por GL_TRIANGLES;
* Terreno formado por GL_TRIANGLE_STRIP;
* A parede formado por GL_TRIANGLE_STRIP;
  
*obs: Vale ressaltar que os vértices utilizados para gerar cada modelo bem como a indexação dos mesmos encontram-se em arquivo obj.

### main.hpp
Construção padrão da classe main vista em aula.
<pre>
  <code >
  #include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    window.setOpenGLSettings({.samples = 4});
    window.setWindowSettings({
        .width = 600,
        .height = 600,
        .title = "LookAt Camera",
    });

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}
  </code>
</pre>

### window.hpp
<pre>
  <code>
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

  positions.push_back(glm::vec2(-2.5f, 0.0f));
  positions.push_back(glm::vec2(-2.5f, -1.0f));
  positions.push_back(glm::vec2(-2.5f, -2.0f));
  positions.push_back(glm::vec2(-2.5f, -3.0f));
  positions.push_back(glm::vec2(2.5f, 0.0f));
  positions.push_back(glm::vec2(2.5f, -1.0f));
  positions.push_back(glm::vec2(2.5f, -2.0f));
  positions.push_back(glm::vec2(2.5f, -3.0f));

  // Lista com todas as configurações dos modelos
  allConfigs.clear();

  auto const bunnyPath = assetsPath + "bunny.obj";
  allConfigs.push_back(
      {glm::vec2(-1.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.15f, 0.45f, false, 0.0f, 0.1f, bunnyPath, false,
       randomSpeed(m_randomEngine), 1.0f});

  auto const catPath = assetsPath + "cat.obj";
  allConfigs.push_back(
      {glm::vec2(0.0f, 0.0f),
       glm::vec3(randomColor(m_randomEngine), randomColor(m_randomEngine),
                 randomColor(m_randomEngine)),
       0.2f, 0.45f, true, -90.0f, 0.005f, catPath, false,
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
      abcg::createOpenGLProgram({{.source = assetsPath + "teste.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "teste.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);

  // Localizacao das variaveis uniformes
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");

  auto const objBasePath = assetsPath + "cilindro.obj";
  m_collection.create(m_program, allConfigs, objBasePath);

  m_ground.create(m_program);
  m_wall.create(m_program);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Configurando as matrizes de projeçao e visao
  abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,
                           &m_camera.getViewMatrix()[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
                           &m_camera.getProjMatrix()[0][0]);

  // Desenhando a coleçao de obras
  m_collection.paint();

  // Desenhando o chao
  m_ground.paint();
  m_wall.paint();

  abcg::glUseProgram(0);
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
  </code>
</pre>
  * glm::ivec2 m_viewportSize : indica o tamanaho da view port.
  * GLuint m_program: referência para o programa utilizado.
  * GLuint m_viewMatrixLocation: referência para a matriz de visão.
  * GLuint m_projMatrixLocation: referência para a matriz de projeção.
  * Camera m_camera: referência para o observador.
  * float m_dollySpeed: variavel responsável por ativar a direção do movimento de trás e frente da camera.
  * float m_truckSpeed: variavel responsável por ativar a direação do movimento lateral da camera.
  * float m_panSpeed: variavel responsável por ativar a direção do giro da camera em seu próprio eixo.
  * Collection m_collection: responsável por gerenciar o acervo do múseu.
  * Ground m_ground: responsável por desenhar o chão.
  * Wall m_wall: responsável por desenhar o chão.
  * std::vector<ObjectConfiguration> allConfigs: Lista de configurações das estátuas.
  * std::vector<glm::vec2> positions: lista de configurações das posições inciais.
  * std::default_random_engine m_randomEngine: Seed para aleatorizar quando será gerado o próximo obstáculo.

 De modo geral, a window.cpp irá criar uma lista aletória de configuralções onde serão selecionados as obras que serão dispostas na tela. As configurações selecionadas serão guardadas em "allConfigs" que será o parametro para 
m_collection. Alguns parametrôs como posição e cores serão definidos de maneira aleatória e outros como escala, altura, etc serão pré-definidos pois eram necessidades dos modelos adotados de se adequarem a cena proposta.

### ObjectConfiguration

Estrutura que define as configurações do modelo
<pre>
  <code>
  struct ObjectConfiguration {
  glm::vec2 startPosition;
  glm::vec3 color;
  float minHigh;
  float maxHigh;
  bool verticalRotate;
  float radiusVerticalRotate;
  float scale;
  std::string path;
  bool choosed;
  float rotationSpeed;
  float triangulesToDraw;
};
</code>
</pre>

* glm::vec2 startPosition : define a posição incial do modelo.
* glm::vec3 color : define a cor do modelo.
* float minHigh : define a posição minima do eixo y.
* float maxHigh : define a posição máxima do eixo y
* bool verticalRotate : defina se será necessário realizar a rotação em outro eixo para ajustar o modelo. Alguns modelos (cat.obj por exemplo) não vieram na posição adequada e necessitam deste parametro.
* float radiusVerticalRotate : define em quanto o modelo irá rotacionar.
* float scale : define a escala do modelo.
* std::string path : caminho do arquivo obj do modelo. 
* float rotationSpeed : define a velocidade de rotação
* float triangulesToDraw : define a porcentagem de triangulos que serão desenhandos. Esse parametro foi adicionado pois alguns modelos (eye.obj) ficaram melhores sem alguns triangulos desenhados.

### ground.cpp

Classe que gera o chão. O código em si é idêntico ao visto em aula apenas adicionei uma linha vermelha para simular um tapete.

<pre>
<code>
 #include "ground.hpp"

void Ground::create(GLuint program) {
  // Unit quad on the xz plane
  std::array<glm::vec3, 4> vertices{{{-0.5f, 0.0f, +0.5f},
                                     {-0.5f, 0.0f, -0.5f},
                                     {+0.5f, 0.0f, +0.5f},
                                     {+0.5f, 0.0f, -0.5f}}};

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create VAO and bind vertex attributes
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  // Save location of uniform variables
  m_modelMatrixLoc = abcg::glGetUniformLocation(program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(program, "color");
}

void Ground::paint() {
  abcg::glBindVertexArray(m_VAO);

  // Draw a grid of 2N+1 x 2N+1 tiles on the xz plane, centered around the
  // origin
  auto const N{5};
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const x : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, 0.0f, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      if (x == 0) {
        // Set color (checkerboard pattern)
        abcg::glUniform4f(m_colorLoc, 1.0f, 0.0, 0.0, 1.0f);
      } else {
        // Set color (checkerboard pattern)
        auto const gray{(z + x) % 2 == 0 ? 1.0f : 0.5f};
        abcg::glUniform4f(m_colorLoc, gray, gray, gray, 1.0f);
      }

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  abcg::glBindVertexArray(0);
}

void Ground::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
</code>
</pre>

* GLuint m_VAO : guarda a referência do VAO.
* GLuint m_VBO: guarda a referência do VBO.
* GLint m_modelMatrixLoc: guarda a localização da matriz de modelo.
* GLint m_colorLoc: guarda a localização da cor.
* void create(GLuint program) : método responsável por criar os vértices, VBO, VBA que serão utilizados.
* void paint() : método responsável por desenhar o grid de quadrados.
* void destroy() : método responsável por destruir VBO e VAO utilizados.


### wall.cpp
Wall é a classe responsável por desenhar as parades da sala. O código foi inspirado no ground.cpp visto em aula apenas transladei para outros planos e rotacionei (no caso das parades traseira e frontal) para se ajustarem ao plano correto pois, inicialmente, o quadrado é iniciado no plano yz.

<pre>
  <code>
    #include "wall.hpp"

void Wall::create(GLuint program) {

  std::array<glm::vec3, 4> vertices{{{0.0f, -0.5f, +0.5f},
                                     {0.0f, -0.5f, -0.5f},
                                     {0.0f, +0.5f, +0.5f},
                                     {0.0f, +0.5f, -0.5f}}};

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create VAO and bind vertex attributes
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  // Save location of uniform variables
  m_modelMatrixLoc = abcg::glGetUniformLocation(program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(program, "color");
}

void Wall::paint() {
  abcg::glBindVertexArray(m_VAO);
  auto const N{5};

  // parede traseira
  for (auto const x : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, y, 5.0f));
      // rotacionando modelo pois o modelo original está no espaço yz
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede frontal
  for (auto const x : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, y, -5.0f));
      // rotacionando modelo pois o modelo original está no espaço yz
      model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede direita
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(5.0f, y, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  // parede esquerda
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const y : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(-5.0f, y, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  abcg::glBindVertexArray(0);
}

void Wall::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}
  </code>
</pre>


* GLuint m_VAO : guarda a referência do VAO.
* GLuint m_VBO: guarda a referência do VBO.
* GLint m_modelMatrixLoc: guarda a localização da matriz de modelo.
* GLint m_colorLoc: guarda a localização da cor.
* void create(GLuint program) : método responsável por criar os vértices, VBO, VBA que serão utilizados.
* void paint() : método responsável por desenhar o grid de quadrados.
* void destroy() : método responsável por destruir VBO e VAO utilizados.


### base.cpp

Classe responsável por desenhar a base cilindrica que ficará embaixo da estátua.
<pre>
  <code>
#include "base.hpp"
#include <unordered_map>

// Explicit specialization of std::hash for Vertex
template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{std::hash<glm::vec3>()(vertex.position)};
    return h1;
  }
};

void Base::loadModelFromFile(std::string_view path) {
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

void Base::create(GLuint program, std::string_view path, glm::vec2 position) {
  startPosition = position;
  m_program = program;

  // Get location of uniform variables
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLocation = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_colorLocation = abcg::glGetUniformLocation(m_program, "color");

  // Load model
  loadModelFromFile(path);

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

void Base::paint() {
  abcg::glBindVertexArray(m_VAO);

  //  Draw white bunny
  glm::mat4 model{1.0f};
  model =
      glm::translate(model, glm::vec3(startPosition.x, high, startPosition.y));
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
  model = glm::scale(model, glm::vec3(0.1f));

  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(m_colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
  abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT,
                       nullptr);

  abcg::glBindVertexArray(0);
}

void Base::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
  abcg::glDeleteBuffers(1, &m_EBO);
}
  </code>
</pre>

* GLuint m_program : referência do programa utilizado.
* GLuint m_VAO: referência do VAO.
* GLuint m_VBO: referência do VBO.
* GLuint m_EBO: referência do EBO.
* GLint m_viewMatrixLocation: referência da localização da matriz de visão.
* GLint m_projMatrixLocation: referência da localização da matriz de projeção.
* GLint m_modelMatrixLocation: referência da localização da matriz do modelo.
* GLint m_colorLocation: referência da localização da cor.
* std::vector<Vertex> m_vertices : conjunto de vértices do modelo.
* std::vector<GLuint> m_indices : conjunto de índices do modelo.
* glm::vec2 startPosition : posição inicial.
* float high: altura da base. 
* void loadModelFromFile(std::string_view path) : método utilizado para carregar o modelo.
* void create(GLuint program, std::string_view path, glm::vec2 position) : método utilizado para carregar os véticos, criar VBO, VAO, EBO que serão utilizados para gerar o modelo.
* void paint() : método responsável por desenhar a base.
* void destroy() : método responsável por destruir os recursos utilizados.


### estatue.cpp
Classe responsável por desenhar a estátua com base nas configurações selecionadas.

<pre>
  <code>
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

void Estatue::create(GLuint program, ObjectConfiguration configuration) {

  // Configurando objeto
  m_program = program;

  startPosition.x = configuration.startPosition.x;
  startPosition.y = configuration.startPosition.y;
  color = configuration.color;
  minHigh = configuration.minHigh;
  maxHigh = configuration.maxHigh;
  verticalRotate = configuration.verticalRotate;
  radiusVerticalRotate = configuration.radiusVerticalRotate;
  scale = configuration.scale;
  path = configuration.path;
  choosed = configuration.choosed;
  rotationSpeed = configuration.rotationSpeed;
  high = configuration.minHigh;
  triangulesToDraw = configuration.triangulesToDraw;

  // Variaveis uniformes
  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLocation = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_colorLocation = abcg::glGetUniformLocation(m_program, "color");

  // Carregando modelo
  loadModelFromFile(path);

  // Gerando VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER,
                     sizeof(m_vertices.at(0)) * m_vertices.size(),
                     m_vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Gerando EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(m_indices.at(0)) * m_indices.size(),
                     m_indices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Criando VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  abcg::glBindVertexArray(m_VAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  abcg::glBindVertexArray(0);
}

void Estatue::update(float deltaTime) {

  // Calculando angulo de rotação
  radius += rotationSpeed * deltaTime;

  // para nao estourar a variável
  if (radius >= 360)
    radius -= 360;

  // alterando altura y do modelo
  if (up)
    high += 0.1 * deltaTime;
  else
    high -= 0.1 * deltaTime;

  // Verificando se o objeto deve subir ou descer
  if (high >= maxHigh)
    up = false;
  if (high <= minHigh)
    up = true;
}
void Estatue::paint() {

  abcg::glBindVertexArray(m_VAO);

  // Desenhando modelo
  glm::mat4 model{1.0f};
  model =
      glm::translate(model, glm::vec3(startPosition.x, high, startPosition.y));
  model = glm::rotate(model, radius, glm::vec3(0, 1, 0));
  // Caso seja necessário rotação
  if (verticalRotate)
    model = glm::rotate(model, glm::radians(radiusVerticalRotate),
                        glm::vec3(1, 0, 0));

  model = glm::scale(model, glm::vec3(scale));

  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(m_colorLocation, color.x, color.y, color.z, 1.0f);

  auto n{m_indices.size()};
  if (triangulesToDraw != 1.0f) {
    n = (int)n * triangulesToDraw;
  }

  abcg::glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);
}

void Estatue::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
  abcg::glDeleteBuffers(1, &m_EBO);
}
  </code>
</pre>

Os campos são os mesmos do objeto ObjectConfiguration.

* void create(GLuint program, ObjectConfiguration configuration) : Configura o modelo com base na configuração recebida por parâmetro.
* void paint() : método responsável por desenhar o modelo.
* void update(float deltaTime) : método responsável por determinar a posição do modelo.
* void destroy() : método responsável por eliminar os recursos utilizados.

### collection.cpp
Classe responsável por gerenciar a lista de bases e estátuas.
<pre>
  <code>
    
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
  </code>
</pre>

* GLuint m_program: referência do programa.
* std::vector<Base> m_bases : lista de bases.
* std::vector<Estatue> m_estatues : lista de estátuas.
* std::string_view objBasePath : caminho do arquivo obj da base.
* void create(GLuint program, std::vector<ObjectConfiguration> configs, std::string_view basePath) : método responsável por criar e configurar a lista de bases e estátuas.
* void paint() : método responsável por desenhar a coleção de bases e estátuas.
* void update(float deltaTime): método responsável por atualizar a posição das estátuas.
* void destroy() : método responsável por liberar os recursos utilizados.

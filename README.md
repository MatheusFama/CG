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
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/ChronoDino.jpeg" width="300">
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
    │   lookat.frag
    └   lookat.vert</code></pre>

### Cenário
O cenário será formado pelos seguintes objetos:
* A plataforma formada por GL_TRIANGLES;
* A estátua formada por GL_TRIANGLES;
* Terreno formado por GL_TRIANGLE_STRIP;
* A parede formado por GL_TRIANGLE_STRIP;
  
*obs: Vale ressaltar que os vértices utilizados para gerar cada modelo bem como a indexação dos mesmos encontram-se num arquivo obj.

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
      abcg::createOpenGLProgram({{.source = assetsPath + "lookat.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "lookat.frag",
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

### gamedata.hpp

Estrutura que define o estado atual do jogo.
<pre>
  <code>
  #ifndef GAMEDATA_HPP_
  #define GAMEDATA_HPP_
  
  #include <bitset>
  
  enum class Input { Idle, Up, Down };
  enum class State { Playing, GameOver };
  struct GameData {
    State m_state{State::Playing};
    Input m_input{Input::Idle};
    GLfloat maxHigh{0.8f};
    GLfloat minHigh{0.0f};
    float scoreTime;
  };
  
  #endif
  </code>
</pre>
* m_state pode ser:
  * State::Playing: a aplicação está em modo de jogo, com o square respondendo aos comandos do jogador;
  * State::GameOver: o jogador perdeu. Nesse caso, square não é exibido e não responde aos comandos do jogador;
* m_input pode ser:
  * Input::Idle : o jogador não realizou nenhuma ação enquanto square está no chão.
  * Input::Up : o jogador pulou com square.
  * Input::Down : square está descendo.
* scoreTime : Representa o tempo feito pelo jogador.
* maxHig,minHigh: Altura máxima e minima alcançada por square.

### square.hpp
Personagem utilizado pelo jogador.
<pre>
<code>
#ifndef SQUARE_HPP_
#define SQUARE_HPP_

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"
#include <list>
class Square {
public:
  void create(GLuint program);
  void paint(GameData const &gameData);
  void destroy();
  void update(GameData const &gameData, float deltaTime);
  glm::vec2 getCenter();

  GLfloat m_translation{0.0};
  glm::vec4 m_color{1};
  glm::vec2 position{-0.85f, 0.03f};
  GLfloat size{0.1f};
  GLfloat jumpDistance{0.8f};
  GLfloat jumpTime{0.4};
  GLfloat fallTime{0.35};

private:
  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLint m_translationLoc{};
};
#endif

</code>
</pre>

* glm::vec2 getCenter: Método que retorna o centro atual do objeto.
* GLfloat m_translation: Referência para guardar a alteração da posição do objeto.
* glm::vec2 position: Posição inicial.
* GLfloat size: Tamanho do objeto.
* GLfloat jumpDistance: Distância máxima de pulo.
* GLfloat jumpTime: Tempo de subida do pulo.
* GLfloat fallTime: Tempo de descida do pulo.
* GLint m_translationLoc: Referência para a variável m_translation que estará na GPU.
  

### obstacles.hpp

Classe que gerencia os obstáculos. No caso, os obstáculos são gerados em um espaço de tempo aleatório e destruídos assim que percorrerem um determinado espaço da tela.
<pre>
<code>
  #ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include <list>
#include <random>

#include "abcgOpenGL.hpp"

#include "gamedata.hpp"
#include "square.hpp"

class Obstacles {
public:
  void create(GLuint program);
  void paint(GameData const &gameData);
  void destroy();
  void update(float deltaTime);
  GLfloat maxDistance{5.5};
  GLfloat distanceTime{3};
  struct Obstacle {
    GLuint m_VAO{};
    GLuint m_VBO{};
    GLfloat m_translation{0.0};
    bool remove{false};
    glm::vec4 m_color{1};
    glm::vec2 position{0.99f, 0.08f};
    float m_height{0.2f};
    float m_base{0.3f};
    //GLfloat translationSpace{0.0001f};
    GLint m_translationLoc{};

    glm::vec2 getCenter() {
      return glm::vec2{position.x + m_translation, position.y};
    };

    void destroy() {
      abcg::glDeleteBuffers(1, &m_VBO);
      abcg::glDeleteVertexArrays(1, &m_VAO);
    };
  };

  std::list<Obstacle> m_obstacles;

  Obstacle makeObstacle();

private:
  GLuint m_program{};
};

#endif
</code>
</pre>

  * GLfloat maxDistance: Distância máxima que será percorrida por cada obstáculo antes de ser destruído.
  * GLfloat distanceTime: Tempo que será utilizado para o obstáculo percorrer a distância.
  * A estrutura Obstacle será composta por:
    * Obstacle:: GLfloat m_translation: Referência para guardar a alteração da posição do obstacle.
    * Obstacle:: bool remove: Flag utilizada para marcar quais obstáculos serão destruídos.
    * Obstacle:: glm::vec2 position: Posição inicial.
    * Obstacle:: float m_height: Tamanho da altura do obstáculo.
    * Obstacle:: float m_base: Tamanho da base do obstáculo. 
    * Obstacle:: GLint m_translationLoc: Referência para a variável m_translation que estará na GPU.
    * Obstacle:: glm::vec2 getCenter():  Método que retorna a posiçao atual do centro do objeto.
    * Obstacle:: void destroy() : Destrói o obstáculo.

  * std::list<Obstacle> m_obstacles : Lista utilizada para gerenciar os obstáculos.
  * Obstacle makeObstacle(): Método utilizado para criar um novo obstáculo.
  * void destroy(): Destrói todos os obstáculos.

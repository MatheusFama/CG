# JumpingSquare
* Nome: Matheus Fama
* RA: 11040615
  
## Descrição
* JumpingSquare é um jogo inspirado no famoso "Chrome Dino" onde o objetivo é sobreviver o maior tempo possível desviando dos obstáculos. Neste jogo, a mecânica é mantida simples, com o uso de formas geométricas primárias, como quadrados e triângulos.

Você pode testar o jogo [aqui](https://matheusfama.github.io/CG.github.io/public/jumpingsquare.html).

### Chrome Dino
<table>
  <tr>
    <td>
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/ChronoDino.jpeg" width="300">
    </td>
  </tr>
</table>

### Jumping Square

<table>
  <tr>
    <td>
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/ezgif.com-optimize.gif" width="300">
    </td>
  </tr>
</table>


## Organização do Projeto
O projeto foi separado nas seguintes classes:

* Square: classe que representará o personagem.
* Obstacle: classe responsável por gerenciar os obstáculos.
* GameData: clase responsável por gerenciar o estado do jogo.
* Ground : classe que representa o terreno.


### Organização dos arquivos
<pre>
<code>jumpingsquare/
│   square.cpp
│   square.hpp
│   ground.cpp
│   ground.hpp
│   obstacle.cpp
│   obstacle.hpp
│   CMakeLists.txt
│   gamedata.hpp
│   main.cpp
│   window.hpp
│   window.cpp
│
└───assets/
    │   Inconsolata-Medium.ttf
    │   ground.frag
    │   ground.vert
    │   objects.frag
    │   objects.vert
    │   obstacle.frag
    └   obstacle.vert</code></pre>

### Cenário
O cenário do jogo será formado pelos seguintes objetos:
* O personagem square formado por GL_TRIANGLES;
* Obstáculos formados por GL_TRIANGLES;
* Terreno formado por GL_LINE_STRIP;

### main.hpp
Construção padrão da classe main vista em aula.
<pre>
  <code >
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
  </code>
</pre>

### window.hpp
<pre>
  <code>
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
  GLuint m_groundProgram{}
  GameData m_gameData;
  Ground m_ground;
  Square m_square;
  Obstacles m_obstacles;
  abcg::Timer m_restartWaitTimer;
  abcg::Timer m_restartGameWaitTimer;
  ImFont *m_font{};
  float randomTime{0.0};
  std::default_random_engine m_randomEngine;
  std::uniform_real_distribution<float> m_randomDist{0.5f, 4.5f};

  void restart();
};

#endif
  </code>
</pre>
  * glm::ivec2 m_viewportSize : indica o tamanaho da view port.
  * GLuint m_objectsProgram: programa que será utilizado em square.
  * GLuint m_obstaclesProgram: programa que será utilizando em obstacle.
  * GLuint m_groundProgram: programa que será utilizando em ground.
  * GameData m_gameData : Para gerenciar o estado do jogo, utilizaremos uma instancia de GameData.
  * Ground m_ground: Referência para ground.
  * Square m_square: Referência para square.
  * Obstacles m_obstacles: Referência para obstacles.
  * abcg::Timer m_restartWaitTimer: Timer que utilizado para indicar quando será criado o proximo obstaculo.
  * abcg::Timer m_restartGameWaitTimer: Timer que utilizado para contar a quantidade de tempo feita pelo jogador e para reiniciar a partida.
  * ImFont *m_font: fonte que será utilizada no jogo.
  * float randomTime: Referência para armazenar o resultado final do jogador.
  * std::default_random_engine m_randomEngine: Seed para aleatorizar quando será gerado o próximo obstáculo.
  * std::uniform_real_distribution<float> m_randomDist: Distribuição para determinar quando será gerado o proximo obstáculo.
  * void restart(): método utilizado para configurar o inicio de cada partida.
  * void checkCollisions() : método utilizado para checar colisões entre obstáculos e square.


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

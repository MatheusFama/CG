# JumpingSquare

## Descrição
* JumpingSquare é um jogo inspirado no famoso "Chrome Dino" onde o objetivo é sobreviver o maior tempo possível desviando dos obstáculos. Neste jogo, a mecânica é mantida simples, com o uso de formas geométricas primárias, como quadrados e triângulos.

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
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/jumpingSquare.png" width="300">
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
    └   obstacle.vert</code>

### Cenário
O cenário do jogo será formado pelos seguintes objetos:
* O personagem square formado por GL_TRIANGLES;
* Obstáculos formados por GL_TRIANGLES;
* Terreno formado por GL_LINE_STRIP;

### main.hpp
Construção padrão da classe main vista em aula.
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
### gamedata.hpp

Estrutura que define o estado atual do jogo.

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

## License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.

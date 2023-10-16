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
};

#endif
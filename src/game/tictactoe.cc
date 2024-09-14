export module tictactoe;

import game;

namespace DamathZero::Game {

export class TicTacToe : public Game {
 public:
  TicTacToe() : Game(10) {}
};

}  // namespace DamathZero::Game
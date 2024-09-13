#include "game/damath.h"

namespace DamathZero::Game {

Board::Board() {
  cells_[0 + 8 * 0] = Operation::Times;
  cells_[2 + 8 * 0] = Operation::Divide;
  cells_[4 + 8 * 0] = Operation::Minus;
  cells_[6 + 8 * 0] = Operation::Plus;

  cells_[1 + 8 * 1] = Operation::Divide;
  cells_[3 + 8 * 1] = Operation::Times;
  cells_[5 + 8 * 1] = Operation::Plus;
  cells_[7 + 8 * 1] = Operation::Minus;

  cells_[0 + 8 * 2] = Operation::Minus;
  cells_[2 + 8 * 2] = Operation::Plus;
  cells_[4 + 8 * 2] = Operation::Times;
  cells_[6 + 8 * 2] = Operation::Divide;

  cells_[1 + 8 * 3] = Operation::Plus;
  cells_[3 + 8 * 3] = Operation::Minus;
  cells_[5 + 8 * 3] = Operation::Divide;
  cells_[7 + 8 * 3] = Operation::Times;

  cells_[0 + 8 * 4] = Operation::Times;
  cells_[2 + 8 * 4] = Operation::Divide;
  cells_[4 + 8 * 4] = Operation::Minus;
  cells_[6 + 8 * 4] = Operation::Plus;

  cells_[1 + 8 * 5] = Operation::Divide;
  cells_[3 + 8 * 5] = Operation::Times;
  cells_[5 + 8 * 5] = Operation::Plus;
  cells_[7 + 8 * 5] = Operation::Minus;

  cells_[0 + 8 * 6] = Operation::Minus;
  cells_[2 + 8 * 6] = Operation::Plus;
  cells_[4 + 8 * 6] = Operation::Times;
  cells_[6 + 8 * 6] = Operation::Divide;

  cells_[1 + 8 * 7] = Operation::Plus;
  cells_[3 + 8 * 7] = Operation::Minus;
  cells_[5 + 8 * 7] = Operation::Divide;
  cells_[7 + 8 * 7] = Operation::Times;

  cells_[0 + 8 * 0].SetPiece({Piece::Color::Blue, 2});
  cells_[2 + 8 * 0].SetPiece({Piece::Color::Blue, -5});
  cells_[4 + 8 * 0].SetPiece({Piece::Color::Blue, 8});
  cells_[6 + 8 * 0].SetPiece({Piece::Color::Blue, -11});

  cells_[1 + 8 * 1].SetPiece({Piece::Color::Blue, -7});
  cells_[3 + 8 * 1].SetPiece({Piece::Color::Blue, 10});
  cells_[5 + 8 * 1].SetPiece({Piece::Color::Blue, -3});
  cells_[7 + 8 * 1].SetPiece({Piece::Color::Blue, 0});

  cells_[0 + 8 * 2].SetPiece({Piece::Color::Blue, 4});
  cells_[2 + 8 * 2].SetPiece({Piece::Color::Blue, -1});
  cells_[4 + 8 * 2].SetPiece({Piece::Color::Blue, 6});
  cells_[6 + 8 * 2].SetPiece({Piece::Color::Blue, -9});

  cells_[1 + 8 * 5].SetPiece({Piece::Color::Red, -9});
  cells_[3 + 8 * 5].SetPiece({Piece::Color::Red, 6});
  cells_[5 + 8 * 5].SetPiece({Piece::Color::Red, -1});
  cells_[7 + 8 * 5].SetPiece({Piece::Color::Red, 4});

  cells_[0 + 8 * 6].SetPiece({Piece::Color::Red, 0});
  cells_[2 + 8 * 6].SetPiece({Piece::Color::Red, -3});
  cells_[4 + 8 * 6].SetPiece({Piece::Color::Red, 10});
  cells_[6 + 8 * 6].SetPiece({Piece::Color::Red, -7});

  cells_[1 + 8 * 7].SetPiece({Piece::Color::Red, -11});
  cells_[3 + 8 * 7].SetPiece({Piece::Color::Red, 8});
  cells_[5 + 8 * 7].SetPiece({Piece::Color::Red, -5});
  cells_[7 + 8 * 7].SetPiece({Piece::Color::Red, 2});
}

Damath::Damath() {}

}  // namespace DamathZero::Game

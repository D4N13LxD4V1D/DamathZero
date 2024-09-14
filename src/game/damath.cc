module;

#include <array>
#include <cstdint>
#include <optional>

export module damath;

namespace DamathZero::Game {

enum class Operation {
  Plus,
  Minus,
  Times,
  Divide,
};

export struct Piece {
  enum class Type : uint8_t {
    Dama,
    Pawn,
  };

  enum class Color : uint8_t {
    Red,
    Blue,
  };

  int value;
  Type type = Type::Pawn;
  Color color;

  Piece(Color color, int value) : value(value), color(color) {}
};

struct Cell {
  std::optional<Piece> piece;
  std::optional<Operation> op;

  Cell(Operation op) : op(op) {}
  Cell() {}

  auto SetPiece(Piece value) { piece = value; }
};

export class Board {
 public:
  Board() {
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

  auto GetOperation(int x, int y) -> std::optional<Operation> {
    return cells_.at(x + y * 8).op;
  }

  auto GetPiece(int x, int y) -> std::optional<Piece> {
    return cells_.at(x + y * 8).piece;
  }

 private:
  std::array<Cell, 8 * 8> cells_;
};

export class Damath {
 public:
  Damath() {}

  auto board() -> Board& { return board_; }

 private:
  Board board_;
};

}  // namespace DamathZero::Game

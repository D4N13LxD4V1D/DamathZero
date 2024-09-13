#pragma once

#include <array>
#include <cstdint>
#include <optional>

namespace DamathZero::Game {

enum class Operation {
  Plus,
  Minus,
  Times,
  Divide,
};

struct Piece {
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

class Board {
 public:
  Board();

  auto GetOperation(int x, int y) -> std::optional<Operation> {
    return cells_.at(x + y * 8).op;
  }

  auto GetPiece(int x, int y) -> std::optional<Piece> {
    return cells_.at(x + y * 8).piece;
  }

 private:
  std::array<Cell, 8 * 8> cells_;
};

class Damath {
 public:
  Damath();

  auto board() -> Board& { return board_; }

 private:
  Board board_;
};

}  // namespace DamathZero::Game

module;

#include <torch/torch.h>

export module game;

import std;

namespace DamathZero::Game {

export class Game {
 public:
  int actionSize;

  Game(int actionSize) : actionSize(actionSize) {}

  virtual ~Game() = default;

  virtual auto Step(torch::Tensor state, int player,
                    torch::Tensor action) -> std::pair<torch::Tensor, int> = 0;

  virtual auto LegalActions(torch::Tensor state,
                            int player) -> torch::Tensor = 0;

  virtual auto Done(torch::Tensor state, int player) -> int = 0;

  virtual auto ToString(torch::Tensor state) -> std::string = 0;
};

}  // namespace DamathZero::Game

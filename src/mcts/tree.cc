module;

#include <torch/torch.h>

export module mcts;

import std;
import game;
import neural;

namespace DamathZero::MCTS {

export class MonteCarloTree {
 public:
  MonteCarloTree(Game::Game* game, torch::nn::Module* network,
                 std::map<std::string, std::string> config)
      : game(game), network(network), config(config) {}

  auto GetActionProbabilities(torch::Tensor state,
                              double temperature = 1.) -> torch::Tensor {
    std::ranges::for_each(
        std::views::iota(0, std::stoi(config["num_simulations"])),
        [this, &state](int) { Search(state); });

    auto s = game->ToString(state);
    auto counts = std::views::iota(0) |
                  std::views::transform([this, &s](int a) {
                    return Nsa.contains({s, a}) ? Nsa[{s, a}] : 0;
                  }) |
                  std::views::take(game->actionSize);

    if (temperature == 0) {
      // bestAs contains the indexes of the best actions
      auto bestAs = std::ranges::max_element(counts);
    }

    return torch::zeros(1);
  }

 private:
  Game::Game* game;
  torch::nn::Module* network;
  std::map<std::string, std::string> config;

  std::map<std::pair<std::string, int>, double>
      Qsa{};  // the Q value of each state-action pair
  std::map<std::pair<std::string, int>, int>
      Nsa{};                        // the visit count of each state-action
  std::map<std::string, int> Ns{};  // the visit count of each state
  std::map<std::string, torch::Tensor> Ps{};  // the state distribution

  std::map<std::string, bool> Es{};           // the end of each state
  std::map<std::string, torch::Tensor> Vs{};  // the value of each state

  auto Search(torch::Tensor state) -> torch::Tensor { return torch::zeros(1); }
};

}  // namespace DamathZero::MCTS
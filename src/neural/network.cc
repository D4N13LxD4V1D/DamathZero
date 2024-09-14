module;

#include <torch/torch.h>

export module neural;

namespace DamathZero::Neural {

export class Network : public torch::nn::Module {
 public:
  Network() {
    register_module("fc1", fc1);
    register_module("fc2", fc2);
    register_module("fc3", fc3);
  }

  auto forward(torch::Tensor x) -> torch::Tensor {
    x = torch::relu(fc1->forward(x));
    x = torch::dropout(x, 0.5, is_training());
    x = torch::relu(fc2->forward(x));
    x = torch::log_softmax(fc3->forward(x), 1);
    return x;
  }

 private:
  torch::nn::Linear fc1{784, 256};
  torch::nn::Linear fc2{256, 128};
  torch::nn::Linear fc3{128, 10};
};

}  // namespace DamathZero::Neural
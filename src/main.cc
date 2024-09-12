#include <torch/torch.h>

#include <cstdint>
#include <iostream>

auto main(std::int32_t arc, const char** argv) -> int {
  std::cout << torch::eye(10) << "\n";

  return 0;
}

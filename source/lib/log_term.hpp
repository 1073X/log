#pragma once

#include <iostream>

#include "observer.hpp"

namespace miu::log {

class log_term : public observer {
  public:
    log_term()
        : observer("term") {}

  private:
    void write(line const& l) override { std::cout << com::to_string(l) << std::endl; }
};

}    // namespace miu::log

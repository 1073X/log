#pragma once

#include <array>

#include "log/ring.hpp"

#include "thread_id.hpp"

namespace miu::log {

class rings {
  public:
    explicit rings(uint32_t capacity);
    ~rings();

    auto capacity() const { return _vec.size(); }
    auto operator[](uint32_t i) { return _vec[i]; }

    ring* get();

  private:
    std::array<ring*, thread_id::max()> _vec;
};

}    // namespace miu::log

#pragma once

#include <array>
#include <com/thread_id.hpp>

#include "log/ring.hpp"

namespace miu::log {

class rings {
  public:
    explicit rings(uint32_t capacity);
    ~rings();

    void resize(uint32_t);

    auto capacity() const { return _vec.size(); }
    auto operator[](uint32_t i) { return _vec[i]; }

    ring* get();

  private:
    std::array<ring*, com::thread_id::max()> _vec;
};

}    // namespace miu::log

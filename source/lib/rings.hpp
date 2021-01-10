#pragma once

#include <array>

#include "ring.hpp"
#include "thread_id.hpp"

namespace miu::log {

class rings {
  public:
    explicit rings(uint32_t capacity)
        : _vec { nullptr } {
        _vec[thread_id::get()] = new ring { capacity };
    }

    ~rings() {
        for (auto ring : _vec) {
            delete ring;
        }
    }

    auto get() {
        auto id = thread_id::get();
        if (UNLIKELY(_vec[id] == nullptr)) {
            uint32_t capacity = _vec[0]->capacity();
            _vec[id] = new ring { capacity };
        }
        return _vec[id];
    }

    auto capacity() const { return _vec.size(); }
    auto operator[](uint32_t i) { return _vec[i]; }

  private:
    std::array<ring*, thread_id::max()> _vec;
};

}    // namespace miu::log

#pragma once

#include <vector>

#include "ring.hpp"
#include "thread_id.hpp"

namespace miu::log {

class rings {
  public:
    rings(uint32_t capacity)
        : _vec(thread_id::max(), nullptr) {
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
            auto capacity = _vec[0]->capacity();
            _vec[id] = new ring { capacity };
        }
        return _vec[id];
    }

  private:
    std::vector<ring*> _vec;
};

}    // namespace miu::log

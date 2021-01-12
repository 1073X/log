
#include "rings.hpp"

namespace miu::log {

rings::rings(uint32_t capacity)
    : _vec { nullptr } {
    _vec[thread_id::get()] = new ring { capacity };
}

rings::~rings() {
    for (auto ring : _vec) {
        delete ring;
    }
}

void
rings::resize(uint32_t cap) {
    for (auto ring : _vec) {
        if (ring) {
            ring->resize(cap);
        }
    }
}

ring*
rings::get() {
    auto id = thread_id::get();
    if (UNLIKELY(_vec[id] == nullptr)) {
        uint32_t capacity = _vec[0]->capacity();
        _vec[id] = new ring { capacity };
    }
    return _vec[id];
}

}    // namespace miu::log

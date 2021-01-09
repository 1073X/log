#pragma once

#include <com/variant.hpp>

#include "head.hpp"

namespace miu::log {

class line {
  public:
    line(head const& h)
        : _head(h) {}

    auto time() const { return _head.time(); }

    auto thread_id() const { return _thread_id; }
    auto set_thread_id(uint32_t v) { _thread_id = v; }

    auto append(com::variant const& var) { _vec.push_back(var); }
    auto begin() const { return _vec.begin(); }
    auto end() const { return _vec.end(); }

  private:
    head _head;
    uint32_t _thread_id { -1U };
    std::vector<com::variant> _vec;
};

}    // namespace miu::log

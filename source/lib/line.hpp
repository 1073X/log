#pragma once

#include <com/variant.hpp>

#include "severity.hpp"

namespace miu::log {

class line {
  public:
    line() = default;
    line(com::datetime time, severity sev)
        : _time(time)
        , _sev(sev) {}

    auto time() const { return _time; }
    auto severity() const { return _sev; }

    auto thread_id() const { return _thread_id; }
    auto set_thread_id(uint32_t v) { _thread_id = v; }

    auto size() const { return _vec.size(); }
    auto append(com::variant const& var) { _vec.push_back(var); }
    auto begin() const { return _vec.begin(); }
    auto end() const { return _vec.end(); }

  private:
    com::datetime _time;
    enum severity _sev { severity::MAX };
    uint32_t _thread_id { -1U };
    std::vector<com::variant> _vec;
};

}    // namespace miu::log

#pragma once
#include <com/variant.hpp>
#include <vector>

#include "severity.hpp"

namespace miu::log {

class line {
  public:
    line() = default;
    line(com::datetime time, severity sev)
        : _time(time)
        , _sev(sev) {}

    auto operator!() const { return _sev == severity::MAX; }
    operator bool() const { return !operator!(); }

    auto time() const { return _time; }
    auto severity() const { return _sev; }

    auto thread_id() const { return _thread_id; }
    auto set_thread_id(uint32_t v) { _thread_id = v; }

    auto size() const { return _vec.size(); }
    auto append(com::variant const& var) { _vec.push_back(var); }
    auto begin() const { return _vec.begin(); }
    auto end() const { return _vec.end(); }

    auto is_intact() const { return _is_intact; }
    auto set_is_intact(bool v) { _is_intact = v; }

  private:
    com::datetime _time;
    enum severity _sev { severity::MAX };
    uint32_t _thread_id { -1U };
    std::vector<com::variant> _vec;
    bool _is_intact { false };
};

}    // namespace miu::log

namespace std {
std::string to_string(miu::log::line const&);
}
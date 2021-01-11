#pragma once

#include "rings.hpp"
#include "severity.hpp"

namespace miu::log {

class frontend {
  public:
    frontend(rings* rings)
        : _rings(rings) {}

    auto set_severity(severity sev) { _sev = sev; }

    template<typename... ARGS>
    auto print(severity sev, ARGS&&... args) {
        if (sev >= _sev) {
            _rings->get()->push(sev, std::forward<ARGS>(args)...);
        }
    }

  private:
    severity _sev { severity::MAX };
    rings* _rings;
};

}    // namespace miu::log

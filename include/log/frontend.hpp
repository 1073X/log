#pragma once

#include "ring.hpp"
#include "severity.hpp"

namespace miu::log {

class rings;

class frontend {
  public:
    frontend(rings*);

    void set_severity(severity);

    template<typename... ARGS>
    auto print(severity sev, ARGS&&... args) {
        if (sev >= _sev) {
            get()->push(sev, std::forward<ARGS>(args)...);
        }
    }

  private:
    ring* get();

  private:
    severity _sev { severity::MAX };
    rings* _rings;
};

}    // namespace miu::log

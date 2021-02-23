#pragma once

#include "ring.hpp"
#include "severity.hpp"

namespace miu::log {

class rings;

class frontend {
  public:
    frontend(rings*);

    auto severity() const { return _sev; }
    void set_severity(enum severity);

    uint32_t capacity() const;

    template<typename... ARGS>
    auto print(enum severity sev, ARGS&&... args) {
        if (sev >= _sev) {
            get()->push(sev, std::forward<ARGS>(args)...);
        }
    }

  private:
    ring* get();

  private:
    enum severity _sev { severity::MAX };
    rings* _rings;
};

}    // namespace miu::log

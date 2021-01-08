#pragma once

#include "com/datetime.hpp"
#include "com/variant.hpp"
#include "log/severity.hpp"

namespace miu::log {

class head {
  public:
    explicit head(severity sev)
        : _time(com::datetime::now())
        , _sev(sev) {}

    auto time() const { return _time; }
    auto severity() const { return _sev; }

  private:
    com::datetime _time;
    enum severity _sev;
};

}    // namespace miu::log

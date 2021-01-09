#pragma once

#include <com/datetime.hpp>
#include <com/variant.hpp>

#include "log/severity.hpp"

namespace miu::log {

class head {
  public:
    head(com::datetime time, severity sev)
        : _time(time)
        , _sev(sev) {}

    explicit head(severity sev)
        : head(com::datetime::now(), sev) {}

    auto time() const { return _time; }
    auto severity() const { return _sev; }

  private:
    com::datetime _time;
    enum severity _sev;
};

}    // namespace miu::log


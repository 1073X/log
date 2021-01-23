#pragma once

#include <com/datetime.hpp>
#include <com/to_string.hpp>
#include <com/variant.hpp>

#include "severity.hpp"

namespace miu::log {

class head {
  public:
    explicit head(severity sev);
    head(com::datetime time, severity sev);

    auto time() const { return _time; }
    auto severity() const { return _sev; }

  private:
    com::datetime _time;
    enum severity _sev;
};

}    // namespace miu::log

DEF_TO_STRING(miu::log::head);
DEF_VARIANT(miu::log::head, CUSTOM_TYPE_ID + 1);

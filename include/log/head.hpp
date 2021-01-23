#pragma once

#include <com/datetime.hpp>
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

namespace miu::com {
template<>
std::string to_string<log::head>(log::head const&);
}

DEF_VARIANT(miu::log::head, CUSTOM_TYPE_ID + 1);

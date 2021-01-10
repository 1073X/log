#pragma once

#include <com/datetime.hpp>
#include <com/variant.hpp>

#include "severity.hpp"

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

namespace miu::com {
template<>
struct strcat::cast<log::head> {
    auto operator()(log::head const& head) {
        std::ostringstream ss;
        ss << '[' << std::to_string(head.time()) << ' ' << std::to_string(head.severity())[0]
           << ']';
        return ss.str();
    }
};
}    // namespace miu::com

DEF_VARIANT(miu::log::head, CUSTOM_TYPE_ID + 1);

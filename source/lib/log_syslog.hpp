#pragma once

#include <syslog.h>

#include <string_view>

#include "observer.hpp"

namespace miu::log {

class log_syslog : public observer {
  public:
    log_syslog(std::string_view name)
        : observer("syslog") {
        auto option   = LOG_ODELAY | LOG_PID;
        auto facility = LOG_USER;
        ::openlog(name.data(), option, facility);
    }

    ~log_syslog() override { closelog(); }

  private:
    void write(line const& l) override {
        auto lev = LOG_DEBUG;
        switch (l.severity()) {
        case severity::INFO:
            lev = LOG_INFO;
            break;
        case severity::WARN:
            lev = LOG_WARNING;
            break;
        case severity::ERROR:
            lev = LOG_ERR;
            break;
        default:
            break;
        }

        auto str = com::to_string(l);
        syslog(lev, "%s", str.c_str());
    }
};

}    // namespace miu::log

#pragma once

#include "frontend.hpp"

namespace miu::log {

class impl;

class log final {
  private:
    log();

  public:
    static log* instance();
    ~log();

    frontend* front();
    void reset(severity, uint32_t cap);                                                  // terminal
    void reset(severity, uint32_t cap, std::string_view path, std::string_view name);    // file
    void reset(severity, uint32_t cap, std::string_view name);                           // syslog
    void dump();

  private:
    class impl* _impl;
};

template<typename... ARGS>
inline void debug(ARGS&&... args) {
    log::instance()->front()->print(severity::DEBUG, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void info(ARGS&&... args) {
    log::instance()->front()->print(severity::INFO, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void warn(ARGS&&... args) {
    log::instance()->front()->print(severity::WARN, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void error(ARGS&&... args) {
    log::instance()->front()->print(severity::ERROR, std::forward<ARGS>(args)...);
}

}    // namespace miu::log

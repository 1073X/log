#pragma once

#include "frontend.hpp"

namespace miu::log {

class impl;

class log final {
  public:
    static log* instance();

    ~log();

    void set_severity(severity);

    template<typename... ARGS>
    auto print(ARGS&&... args) {
        front()->print(std::forward<ARGS>(args)...);
    }

    void dump();

  private:
    log();
    frontend* front();

  private:
    impl* _impl;
};

template<typename... ARGS>
inline void
debug(ARGS&&... args) {
    log::instance()->print(severity::DEBUG, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void
info(ARGS&&... args) {
    log::instance()->print(severity::INFO, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void
warn(ARGS&&... args) {
    log::instance()->print(severity::WARN, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void
error(ARGS&&... args) {
    log::instance()->print(severity::ERROR, std::forward<ARGS>(args)...);
}

}    // namespace miu::log

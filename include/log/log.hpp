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
void
debug(ARGS&&... args) {}

}    // namespace miu::log

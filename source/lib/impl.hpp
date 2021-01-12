#pragma once
#include <memory>    // unique_ptr

#include "log/frontend.hpp"

#include "backend.hpp"
#include "log_term.hpp"
#include "rings.hpp"

namespace miu::log {

class impl {
  public:
    impl()
        : _observer { new log_term }
        , _rings { 512 }
        , _frontend { &_rings }
        , _backend { &_rings, _observer.get() } {}

    template<typename T, typename... ARGS>
    void watch(ARGS&&... args) {
        // TBD: not thread safe
        _observer.reset(new T { std::forward<ARGS>(args)... });
        _backend.watch(_observer.get());
    }

    auto front() { return &_frontend; }
    auto back() { return &_backend; }

  private:
    std::unique_ptr<observer> _observer;
    rings _rings;
    frontend _frontend;
    backend _backend;
};

}    // namespace miu::log

#pragma once
#include <memory>    // unique_ptr

#include "log/frontend.hpp"

#include "backend.hpp"
#include "rings.hpp"

namespace miu::log {

class impl {
  public:
    impl()
        : _rings { 512 }
        , _frontend { &_rings }
        , _backend { &_rings } {}

    ~impl() { delete _observer; }

    template<typename T, typename... ARGS>
    auto watch(ARGS&&... args) {
        std::unique_ptr<observer> ptr { _observer };

        _observer = new T { std::forward<ARGS>(args)... };
        _backend.watch(_observer);
    }

    auto front() { return &_frontend; }
    auto back() { return &_backend; }

  private:
    rings _rings;
    frontend _frontend;
    backend _backend;
    observer* _observer { nullptr };
};

}    // namespace miu::log

#pragma once

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

    auto front() { return &_frontend; }
    auto back() { return &_backend; }

  private:
    rings _rings;
    frontend _frontend;
    backend _backend;
};

}    // namespace miu::log

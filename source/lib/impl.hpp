#pragma once

#include "log/frontend.hpp"

#include "backend.hpp"
#include "rings.hpp"

namespace miu::log {

class impl {
  public:
    impl()
        : _rings(new rings { 512 })
        , _frontend(new frontend { _rings })
        , _backend(new backend { _rings }) {}

    ~impl() {
        delete _backend;
        for (auto ob : _obs) {
            delete ob;
        }
        delete _frontend;
        delete _rings;
    }

    template<typename T, typename... ARGS>
    auto watch(ARGS&&... args) {
        _obs.emplace_back(new T { std::forward<ARGS>(args)... });
        _backend->watch(_obs.back());
    }

    auto front() { return _frontend; }
    auto back() { return _backend; }

  private:
    rings* _rings;
    frontend* _frontend;
    backend* _backend;
    std::vector<observer*> _obs;
};

}    // namespace miu::log

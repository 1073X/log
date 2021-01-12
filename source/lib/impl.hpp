#pragma once
#include <memory>    // unique_ptr

#include "log/frontend.hpp"
#include "log/log.hpp"

#include "backend.hpp"
#include "log_term.hpp"
#include "rings.hpp"

namespace miu::log {

class impl {
  public:
    impl()
        : _rings { 512 }
        , _frontend { &_rings }
        , _backend { &_rings }
        , _ob { new log_term } {}

    auto front() { return &_frontend; }

    template<typename T, typename... ARGS>
    void reset(severity sev, uint32_t cap, ARGS&&... args) {
        // TBD: not thread safe
        _rings.resize(cap);
        _frontend.set_severity(sev);
        _ob.reset(new T { std::forward<ARGS>(args)... });

        info(+"---------------- started ----------------");
    }

    void dump() { _backend.dump(_ob.get()); }

  private:
    rings _rings;
    frontend _frontend;
    backend _backend;

    std::unique_ptr<observer> _ob;
};

}    // namespace miu::log

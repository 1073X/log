

#include "backend.hpp"

#include <list>

#include "log_term.hpp"

namespace miu::log {

log_term g_default_observer;

backend::backend(rings* rings)
    : _rings { rings }
    , _observer { &g_default_observer } {}

void
backend::watch(observer* ob) {
    _observer = ob;
}

void
backend::dump() {
    std::list<line> lines;

    // thread_id is supposed to increase in ascending order
    for (auto i = 0U; i < _rings->capacity() && (*_rings)[i]; i++) {
        while (auto line = (*_rings)[i]->pop()) {
            line.set_thread_id(i);
            lines.push_back(line);
        }
    }

    lines.sort([](auto lhs, auto rhs) { return lhs.time() < rhs.time(); });
    for (const auto& line : lines) {
        _observer->write(line);
    }
}

}    // namespace miu::log

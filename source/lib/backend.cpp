

#include "backend.hpp"

#include <list>

#include "log_term.hpp"

namespace miu::log {

backend::backend(rings* rings, observer* ob)
    : _rings { rings }
    , _observer { ob } {}

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



#include "backend.hpp"

#include <list>

namespace miu::log {

backend::backend(rings* rings)
    : _rings { rings } {}

void
backend::watch(observer* ob) {
    _obs.push_back(ob);
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

    if (!_obs.empty()) {
        for (auto ob : _obs) {
            for (const auto& line : lines) {
                ob->write(line);
            }
        }
    } else {
        for (const auto& line : lines) {
            std::cout << std::to_string(line) << std::endl;
        }
    }
}

}    // namespace miu::log

#pragma once

#include <list>

#include "observer.hpp"
#include "rings.hpp"

namespace miu::log {

class backend {
  public:
    backend(uint32_t capacity)
        : _rings { capacity } {}

    void watch(observer* ob) { _obs.push_back(ob); }

    template<typename... ARGS>
    auto push(ARGS&&... args) {
        _rings.get()->push(std::forward<ARGS>(args)...);
    }

    auto dump() {
        std::list<line> lines;

        // thread_id is supposed to increase in ascending order
        for (auto i = 0; i < _rings.capacity() && _rings[i]; i++) {
            while (auto line = _rings[i]->pop()) {
                line.set_thread_id(i);
                lines.push_back(line);
            }
        }

        lines.sort([](auto lhs, auto rhs) { return lhs.time() < rhs.time(); });

        if (!_obs.empty()) {
            for (auto ob : _obs) {
                for (auto line : lines) {
                    ob->write(line);
                }
            }
        } else {
            for (auto line : lines) {
                std::cout << std::to_string(line) << std::endl;
            }
        }
    }

  private:
    rings _rings;
    std::vector<observer*> _obs;
};

}    // namespace miu::log

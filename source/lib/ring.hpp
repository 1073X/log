#pragma once

#include <com/ring_buffer.hpp>

#include "head.hpp"
#include "line.hpp"

namespace miu::log {

class ring {
  public:
    explicit ring(uint32_t capacity)
        : _raw { capacity } {}

    auto size() const { return _raw.size(); }

    template<typename... ARGS>
    auto push(severity sev, ARGS&&... args) {
        push(head { sev }, std::forward<ARGS>(args)...);
    }

    auto pop() {
        auto total = _raw.size();
        class line line;
        if (total > 1) {
            auto head = _raw[0].get<class head>();
            line.set_time(head->time());
            line.set_severity(head->severity());

            auto constexpr head_id = com::type_id<class head>::value;
            auto idx = 1;
            while (_raw[idx].id() != head_id && --total) {
                line.append(_raw[idx]);
                idx++;
            }
            _raw.dump(idx);
        }
        return line;
    }

  private:
    void push() {}

    template<typename T, typename... ARGS>
    void push(T const& val, ARGS&&... args) {
        _raw.push(val);
        push(std::forward<ARGS>(args)...);
    }

  private:
    com::ring_buffer<com::variant> _raw;
};

}    // namespace miu::log

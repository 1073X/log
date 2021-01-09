#pragma once

#include <com/ring_buffer.hpp>

#include "head.hpp"
#include "line.hpp"
#include "tail.hpp"

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
        auto constexpr head_id = com::type_id<class head>::value;
        auto constexpr tail_id = com::type_id<class tail>::value;

        auto total = _raw.size();
        if (total > 1) {
            auto idx = 0U;

            // move to next head
            while (idx < total && _raw[idx].id() != head_id) {
                idx++;
            }

            if (idx < total) {
                // extract head
                auto head = _raw[idx].get<class head>();
                line l { head->time(), head->severity() };
                idx++;

                // collect items till tail
                while (idx < total) {
                    if (_raw[idx].id() != tail_id) {
                        l.append(_raw[idx]);
                        idx++;
                    } else {
                        _raw.dump(idx);
                        return l;
                    }
                }
            }
        }
        return line {};
    }

  private:
    void push() { _raw.push(tail {}); }

    template<typename T, typename... ARGS>
    void push(T const& val, ARGS&&... args) {
        _raw.push(val);
        push(std::forward<ARGS>(args)...);
    }

  private:
    com::ring_buffer<com::variant> _raw;
};

}    // namespace miu::log

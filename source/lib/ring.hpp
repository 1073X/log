#pragma once

#include <com/predict.hpp>
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
        auto h = head { sev };
        auto size = _raw.capacity() - _raw.size();
        push(size, h, std::forward<ARGS>(args)...);
    }

    auto pop() {
        auto constexpr head_id = com::type_id<head>::value;
        auto constexpr tail_id = com::type_id<tail>::value;

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
                        l.set_is_intact(_raw[idx].get<tail>()->is_intact());
                        _raw.dump(idx);
                        return l;
                    }
                }
            }
        }
        return line {};
    }

  private:
    void push(uint32_t size) { _raw.push(tail { size > 0 }); }

    template<typename T, typename... ARGS>
    void push(uint32_t size, T const& val, ARGS&&... args) {
        if (LIKELY(size > 1)) {
            _raw.push(val);
            push(--size, std::forward<ARGS>(args)...);
        } else {    // size == 1
            push(0);
        }
    }

  private:
    com::ring_buffer<com::variant> _raw;
};

}    // namespace miu::log

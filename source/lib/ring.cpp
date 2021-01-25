
#include "log/ring.hpp"

namespace miu::log {

ring::ring(uint32_t capacity)
    : _raw { capacity } {
}

line ring::pop() {
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
                    _raw.dump(idx + 1);
                    return l;
                }
            }
        }
    }
    return line {};
}

void ring::push(uint32_t size) {
    assert(_raw.capacity() - _raw.size() > 0 && "no more space");
    _raw.push(tail { size > 0 });
}

uint32_t ring::push_variant(uint32_t size, com::variant const& var) {
    if (UNLIKELY(size <= 1)) {
        if (size == 1) {
            push(0);
        }
        size = 0;
    } else {
        _raw.push(var);
        size--;
    }
    return size;
}

uint32_t ring::push_strcat(uint32_t size, com::strcat const& val) {
    auto real = std::min(size - 1, (uint32_t)val.size());
    for (auto i = 0U; i < real; i++) {
        _raw.push(val[i]);
    }
    return size - real;
}

}    // namespace miu::log

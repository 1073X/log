#pragma once

#include <com/predict.hpp>
#include <com/ring_buffer.hpp>
#include <com/system_warn.hpp>
#include <com/to_string.hpp>

#include "head.hpp"
#include "line.hpp"
#include "tail.hpp"

namespace miu::log {

class ring {
  public:
    explicit ring(uint32_t capacity);

    auto resize(uint32_t cap) { _raw.resize(cap); }

    auto capacity() const { return _raw.capacity(); }
    auto size() const { return _raw.size(); }

    template<typename... ARGS>
    auto push(severity sev, ARGS&&... args) {
        auto size = _raw.capacity() - _raw.size();
        push(size, head { sev }, std::forward<ARGS>(args)...);
    }

    line pop();

  private:
    void push(uint32_t size);

    template<typename T, typename... ARGS>
    void push(uint32_t size, T const& val, ARGS&&... args) {
        if (LIKELY(size > 1)) {
            _raw.push(val);
            push(--size, std::forward<ARGS>(args)...);
        } else {
            if (size == 1) {
                push(0);
            }
            SYSTEM_WARN("LOG_OVERFLOW -", val, std::forward<ARGS>(args)...);
        }
    }

  private:
    com::ring_buffer<com::variant> _raw;
};

}    // namespace miu::log

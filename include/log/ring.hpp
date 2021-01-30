#pragma once
#include <com/predict.hpp>
#include <com/ring_buffer.hpp>
#include <com/strcat.hpp>
#include <com/system_warn.hpp>
#include <vector>

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
    uint32_t push_variant(uint32_t, com::variant const&);
    uint32_t push_strcat(uint32_t, com::strcat const&);
    uint32_t push_string(uint32_t, std::string const&);

    void push(uint32_t size);

    template<typename T, typename... ARGS>
    void push(uint32_t size, T const& val, ARGS&&... args) {
        size = push_variant(size, val);
        if (LIKELY(size)) {
            push(size, std::forward<ARGS>(args)...);
        } else {
            SYSTEM_WARN("LOG_OVERFLOW -", val, std::forward<ARGS>(args)...);
        }
    }

    template<typename... ARGS>
    void push(uint32_t size, com::strcat const& val, ARGS&&... args) {
        size = push_strcat(size, val);
        push(size, std::forward<ARGS>(args)...);
    }

    template<typename... ARGS>
    void push(uint32_t size, std::string const& val, ARGS&&... args) {
        size = push_string(size, val);
        push(size, std::forward<ARGS>(args)...);
    }

    template<typename T, typename ALLOCATOR, typename... ARGS>
    void push(uint32_t size, std::vector<T, ALLOCATOR> const& val, ARGS&&... args) {
        size = push_variant(size, +"VEC[");
        for (auto i = 0U; i < val.size() && size; i++) {
            size = push_variant(size, val[i]);
        }
        push(size, +"]", std::forward<ARGS>(args)...);
    }

  private:
    com::ring_buffer<com::variant> _raw;
};

}    // namespace miu::log

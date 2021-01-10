#pragma once

#include <cstdint>    // int32_t

namespace miu::log {

class thread_id {
  public:
    static constexpr int32_t max();
    static int32_t get();
    static void reset();
};

}    // namespace miu::log

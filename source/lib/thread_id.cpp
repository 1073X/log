
#include "thread_id.hpp"

#include <atomic>
#include <com/fatal_error.hpp>
#include <com/predict.hpp>

namespace miu::log {

static std::atomic<uint16_t> g_mask { 0 };
thread_local int32_t g_id { -1 };

int32_t
thread_id::get() {
    if (UNLIKELY(g_id < 0)) {
        for (g_id = 0; g_id < thread_id::max(); g_id++) {
            auto mask = 1U << g_id;
            if (!(g_mask.fetch_or(mask) & mask)) {
                return g_id;
            }
        }

        FATAL_ERROR("too many threads");
    }

    return g_id;
}

void
thread_id::reset() {
    if (g_id >= 0) {
        g_mask.fetch_and(~(1 << g_id));
        g_id = -1;
    }
}

}    // namespace miu::log


#include "log/log.hpp"

#include <time/time.hpp>

#include "impl.hpp"
#include "log_file.hpp"
#include "log_syslog.hpp"

namespace miu::log {

static std::unique_ptr<impl> g_impl { new impl() };

std::string type() {
    return g_impl->type();
}

enum severity severity() {
    return g_impl->severity();
}

uint32_t capacity() {
    return g_impl->capacity();
}

frontend* front() {
    return g_impl->front();
}

void reset(enum severity sev, uint32_t cap) {
    g_impl->reset<log_term>(sev, cap);
}

void reset(enum severity sev, uint32_t cap, std::string_view path, std::string_view name) {
    g_impl->reset<log_file>(sev, cap, path, name, time::today());
}

void reset(enum severity sev, uint32_t cap, std::string_view name) {
    g_impl->reset<log_syslog>(sev, cap, name);
}

void dump() {
    g_impl->dump();
}

}    // namespace miu::log

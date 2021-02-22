
#include "log/log.hpp"

#include <time/time.hpp>

#include "impl.hpp"
#include "log_file.hpp"
#include "log_syslog.hpp"

namespace miu::log {

log* log::instance() {
    static log instance {};
    return &instance;
}

log::log()
    : _impl { new class impl() } {
}

log::~log() {
    delete _impl;
}

void log::reset(severity sev, uint32_t cap) {
    _impl->reset<log_term>(sev, cap);
}

void log::reset(severity sev, uint32_t cap, std::string_view path, std::string_view name) {
    _impl->reset<log_file>(sev, cap, path, name, time::today());
}

void log::reset(severity sev, uint32_t cap, std::string_view name) {
    _impl->reset<log_syslog>(sev, cap, name);
}

void log::dump() {
    _impl->dump();
}

frontend* log::front() {
    return _impl->front();
}

}    // namespace miu::log

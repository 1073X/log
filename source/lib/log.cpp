
#include "log/log.hpp"

#include "impl.hpp"

namespace miu::log {

log*
log::instance() {
    static log instance {};
    return &instance;
}

log::log()
    : _impl { new impl() } {}

log::~log() { delete _impl; }

frontend*
log::front() {
    return _impl->front();
}

void
log::set_severity(severity sev) {
    front()->set_severity(sev);
}

void
log::dump() {
    _impl->back()->dump();
}

}    // namespace miu::log


#include "log/log.hpp"

#include "impl.hpp"

namespace miu::log {

log*
log::instance() {
    static log instance {};
    return &instance;
}

log::log()
    : _impl { new class impl() } {}

log::~log() { delete _impl; }

frontend*
log::front() {
    return _impl->front();
}

}    // namespace miu::log

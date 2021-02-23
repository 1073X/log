
#include "log/frontend.hpp"

#include "rings.hpp"

namespace miu::log {

frontend::frontend(rings* rings)
    : _rings(rings) {
}

void frontend::set_severity(enum severity sev) {
    _sev = sev;
}

uint32_t frontend::capacity() const {
    return _rings->get()->capacity();
}

ring* frontend::get() {
    return _rings->get();
}

}    // namespace miu::log

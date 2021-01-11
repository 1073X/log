
#include "log/frontend.hpp"

#include "rings.hpp"

namespace miu::log {

frontend::frontend(rings* rings)
    : _rings(rings) {}

void
frontend::set_severity(severity sev) {
    _sev = sev;
}

ring*
frontend::get() {
    return _rings->get();
}

}    // namespace miu::log

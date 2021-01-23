
#include "log/head.hpp"

#include <com/strcat.hpp>
#include <com/variant.hpp>
#include <sstream>

namespace miu::log {

head::head(com::datetime time, enum severity sev)
    : _time(time)
    , _sev(sev) {
}

head::head(enum severity sev)
    : head(com::datetime::now(), sev) {
}

}    // namespace miu::log

namespace miu::com {

using log::head;
using log::severity;

template<>
void variant::set<head>(head const& val) {
    new (_value) com::datetime { val.time() };
    *(severity*)(_value + 1) = val.severity();
}

template<>
std::optional<head> variant::get<head>() const {
    auto time = *(com::datetime const*)_value;
    auto sev  = *(log::severity const*)(_value + 1);
    return std::make_optional<head>(time, sev);
}

}    // namespace miu::com

namespace miu::com {
template<>
std::string to_string<log::head>(log::head const& v) {
    auto sev = std::to_string(v.severity());

    std::ostringstream ss;
    ss << '[' << to_string(v.time()) << ' ' << sev[0] << ']';
    return ss.str();
}
}    // namespace miu::com

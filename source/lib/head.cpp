
#include "log/head.hpp"

#include <com/strcat.hpp>
#include <com/variant.hpp>
#include <sstream>
#include <time/time.hpp>

namespace miu::log {

head::head(time::stamp time, enum severity sev)
    : _time(time)
    , _sev(sev) {
}

head::head(enum severity sev)
    : head(time::now(), sev) {
}

}    // namespace miu::log

namespace miu::com {

using log::head;
using log::severity;

template<>
void variant::set<head>(head const& val) {
    new (_value) time::stamp { val.time() };
    *(severity*)(_value + 1) = val.severity();
}

template<>
std::optional<head> variant::get<head>() const {
    auto time = *(time::stamp const*)_value;
    auto sev  = *(log::severity const*)(_value + 1);
    return std::make_optional<head>(time, sev);
}

}    // namespace miu::com

DEF_TO_STRING(miu::log::head) {
    std::ostringstream ss;
    ss << '[' << to_string(v.time()) << ' ' << enum_to_str(v.severity())[0] << ']';
    return ss.str();
}

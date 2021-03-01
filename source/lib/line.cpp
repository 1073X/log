
#include "log/line.hpp"

#include <sstream>

DEF_TO_STRING(miu::log::line) {
    std::ostringstream ss;

    auto time = v.time().time();
    auto tid  = v.thread_id();
    auto sev  = enum_to_str(v.severity())[0];
    ss << "[" << to_string(time) << ' ' << tid << ' ' << sev << "] ";
    for (auto const& var : v) {
        auto str = var.get<std::string>();
        if (str) {
            ss << str.value() << ' ';
        } else {
            ss << '<' << static_cast<uint32_t>(var.id()) << ":UKN> ";
        }
    }

    return ss.str();
}


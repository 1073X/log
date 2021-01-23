
#include "log/line.hpp"

#include <sstream>

DEF_TO_STRING(miu::log::line) {
    std::ostringstream ss;

    auto time      = v.time().time();
    auto thread_id = v.thread_id();
    auto sev       = std::to_string(v.severity())[0];
    ss << "[" << to_string(time) << ' ' << thread_id << ' ' << sev << "] ";
    for (auto const& var : v) {
        switch (var.id()) {
        case type_id<bool>::value:
            ss << (var.get<bool>().value() ? "true " : "false ");
            break;
        case type_id<char>::value:
            ss << var.get<char>().value() << ' ';
            break;
        case type_id<int8_t>::value:
        case type_id<int16_t>::value:
        case type_id<int32_t>::value:
        case type_id<int64_t>::value:
            ss << to_string(var.get<int64_t>().value()) << ' ';
            break;
        case type_id<uint8_t>::value:
        case type_id<uint16_t>::value:
        case type_id<uint32_t>::value:
        case type_id<uint64_t>::value:
            ss << to_string(var.get<uint64_t>().value()) << ' ';
            break;
        case type_id<float>::value:
        case type_id<double>::value:
            ss << to_string(var.get<double>().value()) << ' ';
            break;
        case type_id<const char*>::value:
        case type_id<std::string>::value:
            ss << var.get<std::string>().value() << ' ';
            break;
        case type_id<microseconds>::value:
            ss << var.get<microseconds>().value().count() << "ms ";
            break;
        case type_id<days>::value:
            ss << var.get<days>().value().count() << "days ";
            break;
        case type_id<date>::value:
            ss << to_string(var.get<date>().value()) << ' ';
            break;
        case type_id<daytime>::value:
            ss << to_string(var.get<daytime>().value()) << ' ';
            break;
        case type_id<datetime>::value:
            ss << to_string(var.get<datetime>().value()) << ' ';
            break;
        default:
            ss << '<' << (uint32_t)var.id() << ":UKN"
               << "> ";
            break;
        }
    }

    return ss.str();
}


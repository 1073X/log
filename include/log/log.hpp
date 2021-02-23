#pragma once

#include "frontend.hpp"

namespace miu::log {

extern std::string type();
extern enum severity severity();
extern uint32_t capacity();

extern void reset(enum severity, uint32_t);                                             // terminal
extern void reset(enum severity, uint32_t, std::string_view path, std::string_view);    // file
extern void reset(enum severity, uint32_t, std::string_view);                           // syslog

extern frontend* front();

template<typename... ARGS>
inline void debug(ARGS&&... args) {
    front()->print(severity::DEBUG, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void info(ARGS&&... args) {
    front()->print(severity::INFO, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void warn(ARGS&&... args) {
    front()->print(severity::WARN, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
inline void error(ARGS&&... args) {
    front()->print(severity::ERROR, std::forward<ARGS>(args)...);
}

extern void dump();

}    // namespace miu::log

#include <gtest/gtest.h>

#include <iostream>

#include "log/line.hpp"
#include "log/log.hpp"
#include "source/lib/impl.hpp"
#include "source/lib/observer.hpp"

using miu::log::severity;

TEST(ut_log, terminal) {
    miu::log::log::instance()->reset(severity::DEBUG, 1024);
    miu::log::debug(1, 2, std::string_view("abc"));
    miu::log::info(1, 2, 3, std::vector { 'a', 'b', 'c' });
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::log::instance()->dump();

    miu::com::thread_id::reset();
}

TEST(ut_log, file) {
    miu::log::log::instance()->reset(severity::DEBUG, 1024, "./", "ut_log");
    miu::log::debug(1, 2, 3);
    miu::log::info(1, 2, 3);
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::log::instance()->dump();

    miu::com::thread_id::reset();
}

TEST(ut_log, syslog) {
    miu::log::log::instance()->reset(severity::DEBUG, 1024, "ut_log");
    miu::log::debug(1, 2, 3);
    miu::log::info(1, 2, 3);
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::log::instance()->dump();

    miu::com::thread_id::reset();
}

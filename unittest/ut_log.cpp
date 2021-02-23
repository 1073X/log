#include <gtest/gtest.h>

#include <iostream>

#include "log/line.hpp"
#include "log/log.hpp"
#include "source/lib/impl.hpp"
#include "source/lib/observer.hpp"

using miu::log::severity;

TEST(ut_log, terminal) {
    miu::log::reset(severity::DEBUG, 1024);
    miu::log::debug(1, 2, std::string_view("abc"));
    miu::log::info(1, 2, 3, std::vector { 'a', 'b', 'c' });
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::dump();

    EXPECT_EQ("term", miu::log::type());
    EXPECT_EQ(severity::DEBUG, miu::log::severity());
    EXPECT_EQ(1024, miu::log::capacity());

    miu::com::thread_id::reset();
}

TEST(ut_log, file) {
    miu::log::reset(severity::DEBUG, 1024, "./", "ut_log");
    miu::log::debug(1, 2, 3);
    miu::log::info(1, 2, 3);
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::dump();

    EXPECT_EQ("file", miu::log::type());

    miu::com::thread_id::reset();
}

TEST(ut_log, syslog) {
    miu::log::reset(severity::DEBUG, 1024, "ut_log");
    miu::log::debug(1, 2, 3);
    miu::log::info(1, 2, 3);
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    miu::log::dump();

    EXPECT_EQ("syslog", miu::log::type());

    miu::com::thread_id::reset();
}

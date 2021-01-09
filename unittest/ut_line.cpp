#include <gtest/gtest.h>

#include "source/lib/line.hpp"

using miu::log::severity;

TEST(ut_line, time) {
    miu::log::line line;
    miu::com::datetime time { 2021, 1, 9, 12, 15, 30, 123 };
    line.set_time(time);
    EXPECT_EQ(time, line.time());
}

TEST(ut_line, severity) {
    miu::log::line line;
    EXPECT_EQ(severity::MAX, line.severity());
    line.set_severity(severity::DEBUG);
    EXPECT_EQ(severity::DEBUG, line.severity());
}

TEST(ut_line, thread_id) {
    miu::log::line line;
    EXPECT_EQ(-1U, line.thread_id());
    line.set_thread_id(1);
    EXPECT_EQ(1U, line.thread_id());
}

TEST(ut_line, append) {
    miu::log::line line;

    EXPECT_EQ(0U, line.size());
    line.append(1);
    line.append(+"abc");
    EXPECT_EQ(2U, line.size());

    auto it = line.begin();
    EXPECT_EQ(1, (it++)->get<int32_t>());
    EXPECT_EQ("abc", (it++)->get<const char*>());
    EXPECT_EQ(line.end(), it);
}


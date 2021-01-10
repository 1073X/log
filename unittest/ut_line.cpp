#include <gtest/gtest.h>

#include "source/lib/line.hpp"

using miu::log::severity;

TEST(ut_line, default) {
    miu::log::line line;
    EXPECT_EQ(severity::MAX, line.severity());
    EXPECT_FALSE(line);
}

TEST(ut_line, construct) {
    miu::com::datetime time { 2021, 1, 9, 12, 15, 30, 123 };
    miu::log::line line { time, severity::DEBUG };
    EXPECT_EQ(time, line.time());
    EXPECT_EQ(severity::DEBUG, line.severity());
    EXPECT_TRUE(line);
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

TEST(ut_line, intact) {
    miu::log::line line;
    EXPECT_FALSE(line.is_intact());
    line.set_is_intact(true);
    EXPECT_TRUE(line.is_intact());
}
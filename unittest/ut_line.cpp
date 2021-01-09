#include <gtest/gtest.h>

#include "source/lib/line.hpp"

using miu::log::head;
using miu::log::severity;

TEST(ut_line, time) {
    miu::com::datetime time { 2021, 1, 9, 12, 15, 30, 123 };
    miu::log::line l { head { time, severity::DEBUG } };

    EXPECT_EQ(time, l.time());
}

TEST(ut_line, thread_id) {
    miu::log::line l { head { severity::DEBUG } };
    EXPECT_EQ(-1U, l.thread_id());

    l.set_thread_id(1);
    EXPECT_EQ(1U, l.thread_id());
}

TEST(ut_line, append) {
    miu::log::line l { head { severity::DEBUG } };

    l.append(1);
    l.append(+"abc");

    auto it = l.begin();
    EXPECT_EQ(1, (it++)->get<int32_t>());
    EXPECT_EQ("abc", (it++)->get<const char*>());
    EXPECT_EQ(l.end(), it);
}


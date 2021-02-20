#include <gtest/gtest.h>

#include "log/line.hpp"

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

TEST(ut_line, to_string) {
    miu::com::datetime time { 2021, 1, 9, 12, 15, 30, 123 };
    miu::log::line line { time, severity::DEBUG };
    line.set_thread_id(1);
    line.append(true);
    line.append('a');
    line.append(1);
    line.append(1.5);
    line.append((uint32_t)2);
    line.append(+"abc");
    line.append(std::string("def"));
    line.append(miu::com::microseconds { 1 });
    line.append(miu::com::days { 1 });
    line.append(miu::com::date { 2021, 1, 10 });
    line.append(miu::com::daytime { 23, 17, 30, 0 });
    line.append(miu::com::datetime { 2021, 1, 10, 23, 17, 30, 0 });
    line.append(miu::com::variant());
    line.set_is_intact(true);

    EXPECT_EQ(
        "[12:15:30.000123 1 D] true a 1 1.500000 2 abc def 1us 1d 20210110 23:17:30.000000 "
        "20210110 23:17:30.000000 <255:UKN> ",
        miu::com::to_string(line));
}

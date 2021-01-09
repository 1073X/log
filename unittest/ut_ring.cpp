#include <gtest/gtest.h>

#include "source/lib/ring.hpp"

using miu::com::datetime;
using miu::log::severity;

struct ut_ring : public testing::Test {
    miu::log::ring ring { 32 };
};

TEST_F(ut_ring, push_pop) {
    ring.push(severity::INFO, 1, +"abc");
    ring.push(severity::DEBUG, 2, +"def", 1.2);

    auto line1 = ring.pop();
    EXPECT_EQ(severity::INFO, line1.severity());
    EXPECT_GE(datetime::now(), line1.time());
    auto it1 = line1.begin();
    EXPECT_EQ(1, (it1++)->get<int32_t>());
    EXPECT_EQ(+"abc", (it1++)->get<const char*>());
    EXPECT_EQ(line1.end(), it1);

    auto line2 = ring.pop();
    EXPECT_EQ(severity::DEBUG, line2.severity());
    EXPECT_GE(datetime::now(), line2.time());
    EXPECT_EQ(3U, line2.size());
}

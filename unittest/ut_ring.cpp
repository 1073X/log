#include <gtest/gtest.h>

#include "log/ring.hpp"

using miu::com::datetime;
using miu::log::severity;

struct ut_ring : public testing::Test {
    miu::log::ring ring { 32 };
};

TEST_F(ut_ring, push_pop) {
    ring.push(severity::INFO, 1, +"abc");
    ring.push(severity::DEBUG, 2, +"def", 1.2);

    auto line1 = ring.pop();
    ASSERT_TRUE(line1);
    EXPECT_EQ(severity::INFO, line1.severity());
    EXPECT_GE(datetime::now(), line1.time());
    EXPECT_TRUE(line1.is_intact());
    auto it1 = line1.begin();
    EXPECT_EQ(1, (it1++)->get<int32_t>());
    EXPECT_EQ(+"abc", (it1++)->get<const char*>());
    EXPECT_EQ(line1.end(), it1);

    auto line2 = ring.pop();
    ASSERT_TRUE(line2);
    EXPECT_TRUE(line2.is_intact());
    EXPECT_EQ(severity::DEBUG, line2.severity());
    EXPECT_GE(datetime::now(), line2.time());
    EXPECT_EQ(3U, line2.size());

    EXPECT_FALSE(ring.pop());
}

TEST_F(ut_ring, overflow) {
    ring.push(severity::DEBUG, 0, 1, 2, 3, 4, 5);
    ring.push(severity::INFO, 0, 1, 2, 3, 4, 5);
    ring.push(severity::WARN, 0, 1, 2, 3, 4, 5);
    ring.push(severity::ERROR, 0, 1, 2, 3, 4, 5, +"overflow");

    // system warn
    ring.push(severity::INFO, 6);

    EXPECT_TRUE(ring.pop());
    EXPECT_TRUE(ring.pop());
    EXPECT_TRUE(ring.pop());

    // should be able to push more
    ring.push(severity::DEBUG, 6);

    auto line = ring.pop();
    ASSERT_TRUE(line);
    EXPECT_FALSE(line.is_intact());
    EXPECT_EQ(6U, line.size());
    auto it = line.begin();
    EXPECT_EQ(0, (it++)->get<int32_t>());
    EXPECT_EQ(1, (it++)->get<int32_t>());
    EXPECT_EQ(2, (it++)->get<int32_t>());
    EXPECT_EQ(3, (it++)->get<int32_t>());
    EXPECT_EQ(4, (it++)->get<int32_t>());
    EXPECT_EQ(5, (it++)->get<int32_t>());
    EXPECT_EQ(line.end(), it);

    auto line2 = ring.pop();
    ASSERT_TRUE(line2);
    EXPECT_TRUE(line2.is_intact());
    EXPECT_EQ(6, line2.begin()->get<int32_t>());

    EXPECT_FALSE(ring.pop());
}

TEST_F(ut_ring, strcat) {
    miu::com::strcat strcat { 1, 2, 3 };
    ring.push(severity::DEBUG, 0, strcat, 4, strcat);

    auto line1 = ring.pop();
    ASSERT_TRUE(line1);
    EXPECT_TRUE(line1.is_intact());
    auto it1 = line1.begin();
    EXPECT_EQ(0, (it1++)->get<int32_t>());
    EXPECT_EQ("1", (it1++)->get<std::string>());
    EXPECT_EQ("2", (it1++)->get<std::string>());
    EXPECT_EQ("3", (it1++)->get<std::string>());
    EXPECT_EQ(4, (it1++)->get<int32_t>());
    EXPECT_EQ("1", (it1++)->get<std::string>());
    EXPECT_EQ("2", (it1++)->get<std::string>());
    EXPECT_EQ("3", (it1++)->get<std::string>());
    EXPECT_EQ(line1.end(), it1);
}

TEST_F(ut_ring, strcat_overflow) {
    miu::com::strcat strcat { 0, 1, 2, 3, 4, 5 };
    ring.push(severity::DEBUG, strcat);
    ring.push(severity::DEBUG, strcat);
    ring.push(severity::DEBUG, strcat);
    ring.push(severity::DEBUG, strcat, +"overflow");

    // system warn;
    ring.push(severity::DEBUG, strcat);
}

TEST_F(ut_ring, resize) {
    ring.resize(128);
    EXPECT_EQ(128U, ring.capacity());
}

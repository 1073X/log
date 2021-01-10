#include <gtest/gtest.h>

#include "source/lib/head.hpp"

using miu::com::datetime;
using miu::log::severity;

TEST(ut_head, ctor) {
    miu::log::head head { severity::DEBUG };
    EXPECT_EQ(severity::DEBUG, head.severity());
    EXPECT_GE(datetime::now(), head.time());
}

TEST(ut_head, variant) {
    using miu::com::type_id;

    EXPECT_EQ(33, type_id<miu::log::head>::value);

    miu::log::head head { severity::INFO };
    miu::com::variant var { head };
    EXPECT_EQ(type_id<miu::log::head>::value, var.id());

    auto head2 = var.get<miu::log::head>();
    ASSERT_TRUE(head2.has_value());
    EXPECT_EQ(head.time(), head2->time());
    EXPECT_EQ(severity::INFO, head2->severity());
}

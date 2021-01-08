#include <gtest/gtest.h>

#include "source/lib/head.hpp"

using miu::com::datetime;
using miu::log::severity;

TEST(ut_head, ctor) {
    miu::log::head head { severity::DEBUG };
    EXPECT_EQ(severity::DEBUG, head.severity());
    EXPECT_GE(datetime::now(), head.time());
}

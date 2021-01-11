#include <gtest/gtest.h>

#include "source/lib/frontend.hpp"

using miu::log::severity;

struct ut_frontend : public testing::Test {
    miu::log::rings rings { 32 };
    miu::log::frontend frontend { &rings };
};

TEST_F(ut_frontend, default_severity_max) {
    frontend.print(severity::DEBUG, 1);
    EXPECT_FALSE(rings[0]->pop());
}

TEST_F(ut_frontend, print) {
    frontend.set_severity(severity::WARN);

    frontend.print(severity::DEBUG, 1);
    frontend.print(severity::WARN, 2);
    frontend.print(severity::ERROR, 3);

    auto line1 = rings[0]->pop();
    ASSERT_TRUE(line1);
    EXPECT_EQ(severity::WARN, line1.severity());
    auto line2 = rings[0]->pop();
    ASSERT_TRUE(line2);
    EXPECT_EQ(severity::ERROR, line2.severity());

    EXPECT_FALSE(rings[0]->pop());
}

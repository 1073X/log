#include <gtest/gtest.h>

#include "log/tail.hpp"

using miu::com::type_id;
using miu::log::tail;

TEST(ut_tail, ctor) {
    class tail tail(true);
    EXPECT_TRUE(tail.is_intact());
}

TEST(ut_tail, variant) {
    miu::com::variant var { tail(false) };

    EXPECT_EQ(type_id<tail>::value, var.id());
    EXPECT_TRUE(var.get<tail>());
    EXPECT_FALSE(var.get<tail>()->is_intact());
}

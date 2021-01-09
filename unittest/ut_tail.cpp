#include <gtest/gtest.h>

#include "source/lib/tail.hpp"

using miu::com::type_id;
using miu::log::tail;

TEST(ut_tail, variant) {
    class tail tail;
    miu::com::variant var { tail };

    EXPECT_EQ(type_id<class tail>::value, var.id());
    EXPECT_TRUE(var.get<class tail>());
}

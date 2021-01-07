#include <gtest/gtest.h>

#include <iostream>

namespace miu::log {
extern std::string_view version();
extern std::string_view build_info();
}    // namespace miu::log

TEST(ut_version, version) {
    std::cout << miu::log::version() << std::endl;
    std::cout << miu::log::build_info() << std::endl;
}

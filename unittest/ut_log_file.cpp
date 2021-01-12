#include <gtest/gtest.h>

#include <com/datetime.hpp>

#include "log/line.hpp"
#include "log/severity.hpp"
#include "source/lib/log_file.hpp"

using miu::com::date;

struct ut_log_file : public testing::Test {
    void TearDown() override { std::filesystem::remove(file.pathname()); }

    miu::log::log_file file { "./log_file", "ut_log_file", date { 2021, 1, 12 } };
};

TEST_F(ut_log_file, init_file) {
    auto today = date::today();
    auto pathname = "./log_file/ut_log_file_" + std::to_string(today) + ".log";
    EXPECT_EQ(pathname, file.pathname());

    EXPECT_TRUE(std::filesystem::exists(pathname));

    std::ifstream fs { pathname };
    std::string title;
    std::getline(fs, title);
    std::cout << title << std::endl;
}

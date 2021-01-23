#include <gtest/gtest.h>

#include <com/datetime.hpp>

#include "log/line.hpp"
#include "log/severity.hpp"
#include "source/lib/log_file.hpp"

using miu::com::date;

struct ut_log_file : public testing::Test {
    void TearDown() override { std::filesystem::remove(file.pathname()); }

    date log_date = date { 2021, 1, 12 };
    miu::log::log_file file { "./log_file", "ut_log_file", log_date };
};

TEST_F(ut_log_file, init_file) {
    auto pathname = "./log_file/ut_log_file_" + miu::com::to_string(log_date) + ".log";
    EXPECT_EQ(pathname, file.pathname());

    EXPECT_TRUE(std::filesystem::exists(pathname));

    std::ifstream fs { pathname };
    std::string title;
    std::getline(fs, title);
    std::cout << title << std::endl;
}

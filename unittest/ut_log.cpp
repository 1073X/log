#include <gtest/gtest.h>

#include <iostream>

#include "log/line.hpp"
#include "log/log.hpp"
#include "source/lib/impl.hpp"
#include "source/lib/observer.hpp"
#include "source/lib/thread_id.hpp"

using miu::log::line;

std::vector<line> g_lines;
class mock_observer : public miu::log::observer {
  public:
    mock_observer() { g_lines.clear(); }

  private:
    void write(line const& l) override { g_lines.push_back(l); }
};

TEST(ut_log, log) {
    auto log = miu::log::log::instance();

    log->impl()->watch<mock_observer>();
    log->impl()->front()->set_severity(miu::log::severity::DEBUG);
    miu::log::debug(1, 2, 3);
    miu::log::info(1, 2, 3);
    miu::log::warn(1, 2, 3);
    miu::log::error(1, 2, 3);
    log->impl()->back()->dump();

    EXPECT_EQ(4U, g_lines.size());

    miu::log::thread_id::reset();
}

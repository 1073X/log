#include <gtest/gtest.h>

#include <iostream>

#include "log/log.hpp"
#include "source/lib/thread_id.hpp"

TEST(ut_log, log) {
    auto log = miu::log::log::instance();

    log->set_severity(miu::log::severity::DEBUG);
    log->print(miu::log::severity::DEBUG, 1, 2, 3);
    log->dump();

    miu::log::thread_id::reset();
}

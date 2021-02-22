#include <gmock/gmock.h>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "source/lib/backend.hpp"

using namespace std::chrono_literals;
using miu::log::line;
using miu::log::severity;

struct ut_backend : public testing::Test {
    struct mock : public miu::log::observer {
        MOCK_METHOD(void, write, (line const&));
    } ob;

    miu::log::rings rings { 512 };
    miu::log::backend backend { &rings };
};

MATCHER_P2(CheckLine, thread_id, severity, "") {
    return arg.thread_id() == thread_id && arg.severity() == severity;
}

TEST_F(ut_backend, dump) {
    struct {
        auto wait() {
            std::unique_lock<std::mutex> l { mtx };
            val.wait(l);
        }

        auto notify() { val.notify_one(); }

        std::mutex mtx;
        std::condition_variable val;
    } cv1, cv2;

    rings.get()->push(severity::ERROR, 1);
    std::this_thread::sleep_for(1ms);

    std::thread([&]() {
        rings.get()->push(severity::WARN, 2);
        cv1.notify();
        cv1.wait();
        miu::com::thread_id::reset();
    }).detach();
    cv1.wait();
    std::this_thread::sleep_for(1ms);

    std::thread([&]() {
        rings.get()->push(severity::INFO, 3);
        cv2.notify();
        cv2.wait();
        miu::com::thread_id::reset();
    }).detach();
    cv2.wait();
    std::this_thread::sleep_for(1ms);

    rings.get()->push(severity::DEBUG, 4);

    {
        testing::InSequence seq;
        EXPECT_CALL(ob, write(CheckLine(0U, severity::ERROR)));
        EXPECT_CALL(ob, write(CheckLine(1U, severity::WARN)));
        EXPECT_CALL(ob, write(CheckLine(2U, severity::INFO)));
        EXPECT_CALL(ob, write(CheckLine(0U, severity::DEBUG)));
    }

    backend.dump(&ob);

    cv1.notify();
    cv2.notify();

    miu::com::thread_id::reset();
}

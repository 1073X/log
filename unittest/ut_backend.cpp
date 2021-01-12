#include <gmock/gmock.h>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "source/lib/backend.hpp"

using miu::log::line;
using miu::log::severity;

struct ut_backend : public testing::Test {
    struct mock : public miu::log::observer {
        MOCK_METHOD(void, write, (line const&));
    } ob;

    miu::log::rings rings { 512 };
    miu::log::backend backend { &rings, &ob };
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

    std::thread([&]() {
        rings.get()->push(severity::WARN, 2);
        cv1.notify();
        cv1.wait();
        miu::log::thread_id::reset();
    }).detach();
    cv1.wait();

    std::thread([&]() {
        rings.get()->push(severity::INFO, 3);
        cv2.notify();
        cv2.wait();
        miu::log::thread_id::reset();
    }).detach();
    cv2.wait();

    rings.get()->push(severity::DEBUG, 4);

    {
        testing::InSequence seq;
        EXPECT_CALL(ob, write(CheckLine(0U, severity::ERROR)));
        EXPECT_CALL(ob, write(CheckLine(1U, severity::WARN)));
        EXPECT_CALL(ob, write(CheckLine(2U, severity::INFO)));
        EXPECT_CALL(ob, write(CheckLine(0U, severity::DEBUG)));
    }

    backend.dump();

    cv1.notify();
    cv2.notify();

    miu::log::thread_id::reset();
}

TEST_F(ut_backend, replace_observer) {
    mock ob2;
    backend.watch(&ob2);

    rings.get()->push(severity::DEBUG, +"debug");
    rings.get()->push(severity::ERROR, +"error");

    EXPECT_CALL(ob, write(testing::_)).Times(0);
    EXPECT_CALL(ob2, write(testing::_)).Times(2);
    backend.dump();

    miu::log::thread_id::reset();
}

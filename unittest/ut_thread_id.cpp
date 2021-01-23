#include <gtest/gtest.h>

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include "source/lib/thread_id.hpp"

using miu::log::thread_id;

TEST(ut_thread_id, max) {
    EXPECT_EQ(15, thread_id::max());
}

TEST(ut_thread_id, get) {
    EXPECT_EQ(0U, thread_id::get());
    EXPECT_EQ(0U, thread_id::get());

    std::thread { []() {
        EXPECT_EQ(1U, thread_id::get());
        EXPECT_EQ(1U, thread_id::get());
        thread_id::reset();
    } }.join();

    thread_id::reset();
}

TEST(ut_thread_id, overflow) {
    std::mutex mtx;
    std::condition_variable cv;

    for (auto i = 0; i < thread_id::max(); i++) {
        std::promise<bool> ready;
        std::thread([&]() {
            EXPECT_EQ(i, thread_id::get());
            ready.set_value(true);
            std::unique_lock<std::mutex> l { mtx };
            cv.wait(l);
            thread_id::reset();
        }).detach();
        ready.get_future().get();
    }

    EXPECT_ANY_THROW(thread_id::get());

    cv.notify_all();
}

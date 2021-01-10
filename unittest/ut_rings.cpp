#include <gtest/gtest.h>

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include "source/lib/rings.hpp"

using miu::log::thread_id;

struct ut_rings : public testing::Test {
    void TearDown() override { thread_id::reset(); }

    miu::log::rings rings { 16 };
};

TEST_F(ut_rings, get) {
    auto ring = rings.get();
    ASSERT_NE(nullptr, ring);
    EXPECT_EQ(16U, ring->capacity());

    std::mutex mtx;
    std::condition_variable cv;
    for (auto i = 1; i < thread_id::max(); i++) {
        std::promise<miu::log::ring*> ready;
        std::thread([&]() {
            ready.set_value(rings.get());
            std::unique_lock<std::mutex> l { mtx };
            cv.wait(l);
            thread_id::reset();
        }).detach();
        auto ring = ready.get_future().get();
        ASSERT_NE(nullptr, ring);
        EXPECT_EQ(16U, ring->capacity());
    }

    cv.notify_all();
}

TEST_F(ut_rings, get_by_id) {
    EXPECT_EQ(thread_id::max(), rings.capacity());

    EXPECT_EQ(rings.get(), rings[0]);
    EXPECT_EQ(nullptr, rings[1]);
}

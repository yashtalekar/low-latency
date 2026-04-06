#include <gtest/gtest.h>

#include "low_latency/hello.hpp"

TEST(HelloTest, GreetsByName) {
    EXPECT_EQ(low_latency::greet("world"), "Hello, world!");
}

TEST(HelloTest, GreetsEmpty) {
    EXPECT_EQ(low_latency::greet(""), "Hello, !");
}

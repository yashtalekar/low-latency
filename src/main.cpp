#include <iostream>

#include "low_latency/hello.hpp"

auto main() -> int {
    std::cout << low_latency::greet("world") << '\n';
    return 0;
}

#include <iostream>

#include "low_latency/circ_buffer.hpp"
#include "low_latency/hello.hpp"

auto main() -> int {
    std::cout << low_latency::greet("world") << '\n';

    low_latency::CircBuffer<int, 5> buf;
    for (int i = 1; i <= 7; ++i) {
        buf.push(i);
    }
    while (auto v = buf.pop()) {
        std::cout << *v << ' ';
    }
    std::cout << '\n';
    return 0;
}

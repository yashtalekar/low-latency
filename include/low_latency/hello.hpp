#pragma once

#include <string>

namespace low_latency {

inline auto greet(const std::string& name) -> std::string {
    return "Hello, " + name + "!";
}

}  // namespace low_latency

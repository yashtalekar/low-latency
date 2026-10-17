#pragma once
#include <array>

namespace low_latency {

template <class T, std::size_t N>
class SpscQueue {
    static_assert((N & (N - 1)) == 0, "N must be a power of two");

   private:
    std::array<T, N> data_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;

   public:
};

}  // namespace low_latency
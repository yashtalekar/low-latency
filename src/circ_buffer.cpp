#include <atomic>
#include <cstddef>
#include <iostream>

template <class T, std::size_t N>
class CircBuffer {
   private:
    std::array<T, N> data_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t count_ = 0;

   public:
    // push, pop, size, empty

    void push(const T& a) {
        if (count_ == N) {
            head_ = modularIncrement(head_, N);
        } else {
            ++count_;
        }
        data_[tail_] = a;
        tail_ = modularIncrement(tail_, N);
    }

    size_t modularIncrement(size_t n, size_t modulo) {
        if (n == modulo - 1) {
            n = 0;
        } else {
            ++n;
        }

        return n;
    }

    void pop(const T& a) {}
};
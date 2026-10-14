#include <array>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <optional>

template <class T, std::size_t N>
class CircBuffer {
   private:
    std::array<T, N> data_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t count_ = 0;

    size_t modularIncrement(size_t n, size_t modulo) {
        if (n == modulo - 1) {
            n = 0;
        } else {
            ++n;
        }

        return n;
    }

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

    std::optional<T> pop() {
        if (count_ == 0) {
            return std::nullopt;
        }
        T ret_val = data_[head_];

        head_ = modularIncrement(head_, N);
        --count_;
        return ret_val;
    }

    [[nodiscard]] std::size_t size() const { return count_; }

    [[nodiscard]] bool empty() const { return count_ == 0; }
};
#pragma once

#include <chrono>
#include <string>

namespace euler {

template<typename Clock = std::chrono::high_resolution_clock>
class Timer {
    typename Clock::time_point _start;

public:
    Timer() : _start(Clock::now()) {}

    void stop(double scale = 1e6, std::string format = "Execution time: %.3f\n") {
        auto duration = Clock::now() - _start;
        double time = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / scale;
        printf(format.c_str(), time);
    }
};

}

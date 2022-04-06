#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <chrono>
#include <ctime>
#include <thread>

namespace util::time {

inline void pause(int milliseconds) {
    // https://thispointer.com/how-to-put-a-thread-to-sleep-in-c11-sleep_for-sleep_until/
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

} // namespace util::time

#endif // UTIL_TIME_H
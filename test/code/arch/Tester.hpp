#ifndef TEST_CODE_ARCH_TESTER_HPP
#define TEST_CODE_ARCH_TESTER_HPP

#ifndef NDEBUG
#include <thread>

#define __EXPAND_TO_SLEEP(p_Unit) std::this_thread::sleep_for(std::chrono::p_Unit)

#define WAIT_FOR_MS(p_MS) __EXPAND_TO_SLEEP(milliseconds(p_MS))

#define WAIT_FOR_SECONDS(p_Seconds) __EXPAND_TO_SLEEP(seconds(p_Seconds))

#define WAIT_FOR_MINUTES(p_Minutes) __EXPAND_TO_SLEEP(mintues(p_Minutes))

#else // NDEBUG

#define __EXPAND_TO_SLEEP(p_Unit)

#define WAIT_FOR_MS(p_MS)

#define WAIT_FOR_SECONDS(p_Seconds)

#define WAIT_FOR_MINUTES(p_Minutes)

#endif // NDEBUG

#endif // TEST_CODE_ARCH_TESTER_HPP
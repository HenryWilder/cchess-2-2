#include <chrono>
#include <thread>
#include "Utils.h"

// Get a console handle
HWND window = GetConsoleWindow();

// Get a handle to device context
HDC hdc = GetDC(window);

void SleepForMS(int ms) {
    auto time = std::chrono::milliseconds(ms);
    std::this_thread::sleep_for(time);
}

void SleepForMS(double ms) {
    auto time = std::chrono::microseconds((int)(ms * 1000.0));
    std::this_thread::sleep_for(time);
}

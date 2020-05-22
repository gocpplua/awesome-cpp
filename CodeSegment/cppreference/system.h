﻿#pragma once
inline void t_system() {
#ifdef _WIN32
    std::system("cd");

    //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
       //define something for Windows (64-bit only)
    #else
       //define something for Windows (32-bit only)
    #endif
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    // android
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
    #error "Unknown compiler"
#endif
}

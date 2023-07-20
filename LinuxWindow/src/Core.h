#pragma once
#include <iostream>

#if defined(__linux__)
    #include "Platform/Linux/LinuxWindow.h"
#else
    #define AWINDOW Other
#endif

#define ASSERT(x) if(!(x)) std::cout << "Assertion failed " << #x << std::endl

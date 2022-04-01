#ifndef UTILS_UTILS
#define UTILS_UTILS

#include <filesystem>
#include <Windows.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>

class Utils {
public:
    static auto GetDll(void) -> HMODULE;
public:
    static auto getDebugDir(void) -> std::string;
public:
    static auto debugLog(std::string) -> void;
};

#endif /* UTILS_UTILS */